#include "bsp_key_filter.h"
#include "bsp_gpio.h"
#include "bsp_interrput.h"
#include "bsp_beep.h"

/*
 * @description		: 关闭定时器
 * @param 			: 无
 * @return 			: 无
 */
static void filter_timer_stop(void)
{
	EPIT1->CR &= ~(1<<0);	/* 关闭定时器 */
}

/*
 * @description		: 重启定时器
 * @param - value	: 定时器EPIT计数值
 * @return 			: 无
 */
static void filter_timer_restart(unsigned int value)
{
	EPIT1->CR &= ~(1<<0);	/* 先关闭定时器 */
	EPIT1->LR = value;		/* 计数值 			*/
	EPIT1->CR |= (1<<0);	/* 打开定时器 		*/
}

/*
 * @description		: 定时器中断处理函数 
 * @param			: 无
 * @return 			: 无
 */
static void filter_timer_irq_handler(unsigned int giccIar, void *param)
{ 
	static unsigned char state = OFF;

    if (EPIT1->SR & (1 << 0))               /* 判断比较事件是否发生 */
    {
		filter_timer_stop();					/* 关闭定时器 */
		if(gpio_pin_read(GPIO1, 18) == 0)	/* KEY0 */
		{
			state = !state;
			beep_controller(state);				/* 反转蜂鸣器 */
		}
	}
		
	EPIT1->SR |= 1<<0; 						/* 清除中断标志位 */
}

/*
 * @description		: 初始化用于消抖的定时器，默认关闭定时器
 * @param - value	: 定时器EPIT计数值
 * @return 			: 无
 */
static void key_filter_timer_init(unsigned int value)
{
	EPIT1->CR = 0;	//先清零
	
	/*
     * CR寄存器:
     * bit25:24 01 时钟源选择Peripheral clock=66MHz
     * bit15:4  0  1分频
     * bit3:	1  当计数器到0的话从LR重新加载数值
     * bit2:	1  比较中断使能
     * bit1:    1  初始计数值来源于LR寄存器值
     * bit0:    0  先关闭EPIT1
     */
    EPIT1->CR = (1 << 24 | 1 << 3 | 1 << 2 | 1 << 1);

    /* 计数值    */
	EPIT1->LR = value;
	
	/* 比较寄存器，当计数器值和此寄存器值相等的话就会产生中断 */
	EPIT1->CMPR	= 0;	
	
	GIC_EnableIRQ(EPIT1_IRQn);	/* 使能GIC中对应的中断 */
	
	/* 注册中断服务函数		    */
	system_register_irq_handler(EPIT1_IRQn, filter_timer_irq_handler, NULL);	
}

/*
 * @description		: GPIO中断处理函数
 * @param			: 无
 * @return 			: 无
 */
static void gpio1_16_31_irq_handler(unsigned int giccIar, void *param)
{ 
	/* 开启定时器 */
	filter_timer_restart(66000000/100);

	/* 清除中断标志位 */
	gpio_clear_interrput_flags(GPIO1, 18);
}

/*
 * @description		: 按键初始化
 * @param			: 无
 * @return 			: 无
 */
void imx6ull_filter_key_init(void)
{	
	GPIO_Config key_config;
	
	/* 1、初始化IO复用 */
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);	/* 复用为GPIO1_IO18 */

	/* 2、、配置GPIO1_IO18的IO属性	
	 *bit 16:0 HYS关闭
	 *bit [15:14]: 11 默认22K上拉
	 *bit [13]: 1 pull功能
	 *bit [12]: 1 pull/keeper使能
	 *bit [11]: 0 关闭开路输出
	 *bit [7:6]: 10 速度100Mhz
	 *bit [5:3]: 000 关闭输出
	 *bit [0]: 0 低转换率
	 */
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);
	
	/* 3、初始化GPIO为中断 */
	key_config.direction = GPIO_INPUT;
	key_config.interrupt_mode = GPIO_INT_FALLING_EDGE;
	key_config.output_level = GPIO_LEVLE_HIGH;

	gpio_pin_config(GPIO1, 18, &key_config);

	GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn); /* 使能GIC中对应的中断   		  */
	
	/* 注册中断服务函数 */
	system_register_irq_handler(GPIO1_Combined_16_31_IRQn, gpio1_16_31_irq_handler, NULL);
	
	gpio_enable_interrput(GPIO1, 18);		/* 使能GPIO1_IO18的中断功能 */

	key_filter_timer_init(66000000/100);	/* 初始化定时器,10ms */
}





