#include "imx6ull_register.h"

void clk_enable(void)
{
    CCM->CCGR0 = 0XFFFFFFFF;
    CCM->CCGR1 = 0XFFFFFFFF;
    CCM->CCGR2 = 0XFFFFFFFF;
    CCM->CCGR3 = 0XFFFFFFFF;
    CCM->CCGR4 = 0XFFFFFFFF;
    CCM->CCGR5 = 0XFFFFFFFF;
    CCM->CCGR6 = 0XFFFFFFFF;
}

void led_init(void)
{
    /* 配置GPIO1 IO3引脚复用 */
    IOMUX_SW_MUX->GPIO1_IO03 = 0X5;

    /* 
        配置GPIO1_IO03的IO属性	
        bit 16:0 HYS关闭
        bit [15:14]: 00 默认下拉
        bit [13]: 0 kepper功能
        bit [12]: 1 pull/keeper使能
        bit [11]: 0 关闭开路输出
        bit [7:6]: 10 速度100Mhz
        bit [5:3]: 110 R0/6驱动能力
        bit [0]: 0 低转换率
     */
    IOMUX_SW_PAD->GPIO1_IO03 = 0x10B0;

    /* 设置IO3为输出模式 */
    GPIO1->GDIR = 0X0000008;

    /* 初始化IO3输出0 */
    GPIO1->DR &= ~(1 << 3);	
}

/*
 * @description	: 短时间延时函数
 * @param - n	: 要延时循环次数(空操作循环次数，模式延时)
 * @return 		: 无
 */
void delay_short(volatile unsigned int n)
{
	while(n--){}
}

/*
 * @description	: 延时函数,在396Mhz的主频下
 * 			  	  延时时间大约为1ms
 * @param - n	: 要延时的ms数
 * @return 		: 无
 */
void delay(volatile unsigned int n)
{
	while(n--)
	{
		delay_short(0x7ff);
	}
}

/*
 * @description	: 打开LED灯
 * @param 		: 无
 * @return 		: 无
 */
void led_on(void)
{
	/* 将GPIO1_DR的bit3清零 	*/
	GPIO1->DR &= ~(1<<3); 
}

/*
 * @description	: 关闭LED灯
 * @param 		: 无
 * @return 		: 无
 */
void led_off(void)
{
	/* 将GPIO1_DR的bit3置1 */
	GPIO1->DR |= (1<<3); 
}

int main(int argc, char const *argv[])
{
    clk_enable();		/* 使能所有的时钟 */
	led_init();			/* 初始化led */

	while(1)			
	{	
		led_off();		/* 关闭LED */
		delay(500);		/* 延时500ms */

		led_on();		/* 打开LED */
		delay(500);		/* 延时500ms */
	}

    return 0;
}
