/***************************************************************
文件名	: 	 bsp_exit.c
其他	   : 配置按键对应的GPIP为中断模式
***************************************************************/
#include "bsp_exti.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_interrput.h"

/*
 * @description			: GPIO1_IO18最终的中断处理函数
 * @param				: 无
 * @return 				: 无
 */
static void gpio1_io18_irq_handler(void)
{ 
	static unsigned char state = 0;

	/*
	 *采用延时消抖，中断服务函数中禁止使用延时函数！因为中断服务需要
	 *快进快出！！这里为了演示所以采用了延时函数进行消抖，后面我们会讲解
	 *定时器中断消抖法！！！
 	 */

	delay(10);
	if(gpio_pin_read(GPIO1, 18) == 0)	/* 按键按下了  */
	{
		state = !state;
		beep_controller(state);
	}
	
	gpio_clear_interrput_flags(GPIO1, 18); /* 清除中断标志位 */
}

/*
 * @description			: 初始化外部中断
 * @param				: 无
 * @return 				: 无
 */
void imx6ull_exti_key_init(void)
{
	GPIO_Config key_config;

	/* 1、设置IO复用 */
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);			/* 复用为GPIO1_IO18 */
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

	/* 2、初始化GPIO为中断模式 */
	key_config.direction = GPIO_INPUT;
	key_config.interrupt_mode = GPIO_INT_FALLING_EDGE;
	key_config.output_level = GPIO_LEVLE_HIGH;
	gpio_pin_config(GPIO1, 18, &key_config);

	GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);				/* 使能GIC中对应的中断 */
	system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler)gpio1_io18_irq_handler, NULL);	/* 注册中断服务函数 */
	gpio_enable_interrput(GPIO1, 18);								/* 使能GPIO1_IO18的中断功能 */
}




