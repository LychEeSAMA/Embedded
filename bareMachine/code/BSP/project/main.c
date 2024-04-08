#include "clock.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"

/*
 * @description	: mian函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	clk_enable();		/* 使能所有的时钟 */
	led_init();			/* 初始化led 	*/
	beep_init(); 		/* 初始化蜂鸣器 */
	key_init(); 		/* 按键初始化 */

	while (1)
	{
		switch (get_key_value())
		{
		case KEY_PRESS:
			led_controller(LED0, LED_ON);
			beep_controller(BEEP_ON);
			break;
		
		case KEY_RELEASE:
			led_controller(LED0, LED_OFF);
			beep_controller(BEEP_OFF);
			break;
		
		default:
			break;
		}
		delay(10);
	}

	return 0;
}
