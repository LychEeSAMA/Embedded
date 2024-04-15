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
#include "bsp_rtc.h"
#include "bsp_ap3216c.h"

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
	
	while(ap3216c_init())		/* 检测不到AP3216C */
	{
		lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Check Failed!");
		delay_ms(500);
		lcd_show_string(30, 130, 200, 16, 16, (char*)"Please Check!        ");
		delay_ms(500);
	}	

	unsigned char key = 0;
	int i = 3, t = 0;
	unsigned short ir, als, ps;
	char buf[160];
	struct rtc_datetime rtcdate;
	memset(buf, 0, sizeof(buf));

	while (1)
	{
		if (t == 100) // 1s时间到了
		{
			t = 0;
			lcd_clear(LCD_WHITE);
			sprintf(buf, "will be running %ds......", i);
			lcd_show_string(50, 90, 300, 16, 16, buf);
			i--;
			if (i < 0)
				break;
		}

		key = key_get_value();
		if (key == KEY_PRESS)
		{
			rtcdate.year = 2024;
			rtcdate.month = 4;
			rtcdate.day = 15;
			rtcdate.hour = 11;
			rtcdate.minute = 45;
			rtcdate.second = 0;
			rtc_set_date_time(&rtcdate); /* 初始化时间和日期 */
			break;
		}

		delay_ms(10);
		t++;
	}
	tftlcd_dev.forecolor = LCD_RED;
	lcd_fill(50, 90, 370, 110, tftlcd_dev.backcolor);			   /* 清屏 */
	lcd_show_string(50, 90, 200, 16, 16, (char *)"Current Time:"); /* 显示字符串 */
	tftlcd_dev.forecolor = LCD_BLUE;

	lcd_clear(LCD_WHITE);
	lcd_show_string(30, 50, 200, 16, 16, (char*)"ALPHA-IMX6U IIC TEST");  
	lcd_show_string(30, 70, 200, 16, 16, (char*)"AP3216C TEST");  
	lcd_show_string(30, 90, 200, 16, 16, (char*)"Twei ADD");  
	lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Ready!");  
    lcd_show_string(30, 160, 200, 16, 16, (char*)" IR:");	 
	lcd_show_string(30, 180, 200, 16, 16, (char*)" PS:");	
	lcd_show_string(30, 200, 200, 16, 16, (char*)"ALS:");

	while(1)					
	{	
		rtc_get_date_time(&rtcdate);
		sprintf(buf,"%d/%d/%d %d:%d:%d",rtcdate.year, rtcdate.month, rtcdate.day, rtcdate.hour, rtcdate.minute, rtcdate.second);
		lcd_fill(50,110, 300,130, tftlcd_dev.backcolor);
		lcd_show_string(50, 110, 250, 16, 16, (char *)buf); /* 显示字符串 */

		ap3216c_read_data(&ir, &ps, &als);		/* 读取数据		  	*/
		lcd_shownum(30 + 32, 160, ir, 5, 16);	/* 显示IR数据 		*/
        lcd_shownum(30 + 32, 180, ps, 5, 16);	/* 显示PS数据 		*/
        lcd_shownum(30 + 32, 200, als, 5, 16);	/* 显示ALS数据 	*/ 

		delay_ms(120);	/* 延时一秒 */
	}

	return 0;
}
