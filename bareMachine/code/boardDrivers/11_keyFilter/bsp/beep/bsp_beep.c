#include "bsp_beep.h"

/*
 * @description	: 蜂鸣器初始化
 * @param 		: 无
 * @return 		: 无
 */
void imx6ull_beep_init(void)
{
	/* 1、初始化IO复用 */
	IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);		/* 复用为GPIO5_IO01 */
	
	/* 2、、配置GPIO1_IO03的IO属性	
	 *bit 16:0 HYS关闭
	 *bit [15:14]: 00 默认下拉
	 *bit [13]: 0 kepper功能
	 *bit [12]: 1 pull/keeper使能
	 *bit [11]: 0 关闭开路输出
	 *bit [7:6]: 10 速度100Mhz
	 *bit [5:3]: 110 R0/6驱动能力
	 *bit [0]: 0 低转换率
	 */
	IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0X10B0);
	
	/* 3、初始化GPIO,GPIO1_IO03设置为输出 */
	GPIO5->GDIR |= (1 << 1);	 

	/* 4、设置GPIO1_IO03输出低电平，打开LED0*/
	GPIO5->DR |= (1 << 1);		
}

/* 设置蜂鸣器引脚高低电平 value 0 低电平 1 高电平 */
void beep_set_pin(int value)
{
    GPIO5->DR &= ~(1 << 1);   
    GPIO5->DR |= (1 << value);   
}

/*
 * @description	: 蜂鸣器控制器
 * @param 		: 0 打开 1 关闭
 * @return 		: 无
 */
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
