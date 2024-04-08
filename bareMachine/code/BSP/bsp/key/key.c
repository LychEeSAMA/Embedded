#include "key.h"
#include "bsp_common.h"

/* 按键初始化 */
void key_init(void)
{
    /* 将UART1_CTS_B复用为GPIO */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    /* 配置UART1_CTS_B的电器属性 */
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    /* 设置gpio18为输入模式 */
	GPIO1->GDIR &= ~(1 << 18);
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
    static u8 key_state = KEY_RELEASE;
    while (1)
    {
        if (KEY_RELEASE == key_state && KEY_PRESS == get_cur_key_value())
        {
            delay(10);
            if (KEY_PRESS == get_cur_key_value())
            {
                key_state = KEY_PRESS;
                return KEY_PRESS;
            } 
        }
        else if (KEY_RELEASE == get_cur_key_value())
        {
            delay(10);
            if (KEY_RELEASE == get_cur_key_value())
            {
                key_state = KEY_RELEASE;
                return KEY_RELEASE;
            } 
        }
    }

    return key_state; 
}


void key_init_register(void)
{
   
}

