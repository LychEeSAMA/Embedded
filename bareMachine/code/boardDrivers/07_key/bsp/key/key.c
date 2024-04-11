#include "key.h"
#include "bsp_common.h"

/*!
 * @note NXP官方提供了操作寄存器地址的函数接口与对应寄存器的宏定义，这就让我们可以快速的进行寄存器配置
 *       一个外设使用的流程一般如为：1.使能外设时钟-->2.设置引脚的功能复用(复用为GPIO或I2C_SCL等)-->3.配置复用后引脚的电器属性
 *       -->4.设置引脚做输入或输出-->5.向DR寄存器写入数据
 * 		 在配置引脚电器属性时 做输出的引脚和做输入的引脚会略有不同 但是大同小异
 */

/* 按键初始化 */
void key_init(void)
{
    GPIO_Config keyConfig = {
        .direction = GPIO_INPUT,
        .output_level = GPIO_LEVLE_LOW /* 这里是用这个引脚做输入的  没有输出功能 */
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
		ret = KEY_RELEASE; /* 只要按键松开release标记就会被还原 */
		release = 1; 	/* 标记按键释放 */
	}

	return ret;	
}
