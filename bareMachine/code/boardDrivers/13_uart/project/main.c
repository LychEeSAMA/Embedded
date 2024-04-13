#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_exti.h"
#include "bsp_interrput.h"
#include "bsp_epit_timer.h"
#include "bsp_key_filter.h"
#include "bsp_uart.h"

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	imx6ull_clk_init();	      /* 初始化系统时钟 */
	imx6ull_interrput_init(); /* 中断初始化函数 */
	imx6ull_clk_enable();	  /* 使能所有的时钟 */
	imx6ull_delay_init();     /* 延时有关硬件初始化,主要是GPT定时器 */
	imx6ull_led_init();		  /* 初始化led */
	imx6ull_beep_init();	  /* 初始化beep */

	// imx6ull_key_init();		         /* 初始化key */
	// imx6ull_exti_key_init();          /* 中断按键初始化 */
	// imx6ull_epit1_timer_init(0, 500); /* 初始化EPIT1定时器，1分频 500ms触发一次 */

	imx6ull_filter_key_init(); /* 中断按键 定时器消抖 */
	imx6ull_uart_init();     /* 初始化串口，波特率115200 */

	unsigned char a = 0;
	unsigned char state = OFF;

	while(1)				
	{	
		puts("请输入1个字符:");
		a=getc();
		putc(a);	//回显功能
		puts("\r\n");

		//显示输入的字符
		puts("您输入的字符为:");
		putc(a);
		puts("\r\n\r\n");
		
		state = !state;
		led_controller(LED0,state);
	}

	return 0;
}
