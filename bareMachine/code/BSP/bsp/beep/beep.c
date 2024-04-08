#include "beep.h"
#include "delay.h"
#include "bsp_common.h"

/* 蜂鸣器初始化 */
void beep_init(void)
{
    /* 将SNVS_TAMPER1复用为GPIO */
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    /* 配置SNVS_TAMPER1的电器属性 */
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10b0);

    /* 设置gpio5为输出 */
	GPIO5->GDIR |= (1 << 1);
    /* 初始化时设置beep为高电平 beep关 */
	GPIO5->DR |= (1 << 1);		
}

/* 设置蜂鸣器引脚高低电平 value 0 低电平 1 高电平 */
void beep_set_pin(int value)
{
    GPIO5->DR &= ~(1 << 1);   
    GPIO5->DR |= (1 << value);   
}

/* 蜂鸣器控制器 */
void beep_controller(BeepAction action)
{   
    switch (action)
    {
    case BEEP_ON:
        beep_set_pin(BEEP_ON);
        break;
    
    case BEEP_OFF:
        beep_set_pin(BEEP_OFF);
        break;
    
    default:
        break;
    }
}

