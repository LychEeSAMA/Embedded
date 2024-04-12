#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_exti.h"
#include "bsp_interrput.h"

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	unsigned char led_state = OFF;

	imx6ull_clk_init();	      /* 初始化系统时钟 */
	imx6ull_interrput_init(); /* 中断初始化函数 */
	imx6ull_clk_enable();	  /* 使能所有的时钟 */
	imx6ull_led_init();		  /* 初始化led */
	imx6ull_beep_init();	  /* 初始化beep */
	imx6ull_key_init();		  /* 初始化key */
	imx6ull_exti_key_init();  /* 中断按键初始化 */

	while(1)			
	{	
		led_state = !led_state;
		led_controller(LED0, led_state);
		delay(500);
	}

	return 0;
}
