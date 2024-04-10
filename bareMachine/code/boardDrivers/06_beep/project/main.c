#include "clock.h"
#include "delay.h"
#include "led.h"
#include "beep.h"

/*
 * @description	: mian函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	clk_enable();		/* 使能所有的时钟 */
	led_init();			/* 初始化led 	*/
	beep_init();        /* 蜂鸣器初始化 */

	while (1)
	{
		led_controller(LED0, LED_ON);
		beep_controller(BEEP_ON);
		delay(500);
		led_controller(LED0, LED_OFF);
		beep_controller(BEEP_OFF);
		delay(500);
	}

	return 0;
}
