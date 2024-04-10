#include "key.h"
#include "bsp_common.h"

/* 按键初始化 */
void key_init(void)
{
    GPIO_Config keyConfig = {
        .direction = GPIO_INPUT,
        .output_level = GPIO_LEVLE_LOW
    };
    /* 将UART1_CTS_B复用为GPIO */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    /* 配置UART1_CTS_B的电器属性 */
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);


    /* 设置gpio18为输入模式 */
	// GPIO1->GDIR &= ~(1 << 18);
    gpio_pin_config(GPIO1, 18, &keyConfig);
}

/* 获取按键的gpio值 0按下 1释放 */
static int get_cur_key_value(void)
{
    int ret = KEY_RELEASE;
    ret = gpio_pin_read(GPIO1, 18);
    return ret;    
}

/* 获取消抖后的按键值 */
int get_key_value(void)
{
    int ret = 0;
	static unsigned char release = 1; /* 按键松开 */ 

	if((release == 1) && (get_cur_key_value() == 0)) 		/* KEY0 */
	{	
		delay(10);		/* 延时消抖 		*/
		release = 0;	/* 标记按键按下 */
		if(get_cur_key_value() == 0)
			ret = KEY_PRESS;
	}
	else if(get_cur_key_value() == 1)
	{
		ret = KEY_RELEASE;
		release = 1; 	/* 标记按键释放 */
	}

	return ret;	
}
