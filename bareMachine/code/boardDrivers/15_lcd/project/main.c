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
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"

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

	imx6ull_filter_key_init(); /* 中断按键 定时器消抖 */
	imx6ull_uart_init();	   /* 初始化串口，波特率115200 */
	imx6ull_lcd_init();		   /* 初始化LCD */

	tftlcd_dev.forecolor = LCD_BLACK;
	lcd_clear(LCD_WHITE);
	lcd_show_string(10, 40, 260, 32, 32, (char *)"ALPHA IMX6U");
	lcd_show_string(10, 80, 240, 24, 24, (char *)"Twei LCD Test");
	lcd_show_string(10, 110, 240, 16, 16, (char *)"QQ 987167021");
	lcd_show_string(10, 130, 240, 12, 12, (char *)"2024/4/14");

	while (1)
	{
		delay_ms(100);
	}
	

	return 0;
}
