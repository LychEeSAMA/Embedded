#include "clock.h"
#include "delay.h"
#include "led.h"

/*
 * @description	: mian函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	clk_enable();		/* 使能所有的时钟 */
	led_init();			/* 初始化led 	*/

	while (1)
	{
		led_controller(LED0, LED_ON);
		delay(500);
		led_controller(LED0, LED_OFF);
		delay(500);
	}

	return 0;
}
