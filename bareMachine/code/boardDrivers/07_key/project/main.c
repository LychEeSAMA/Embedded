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
	int i = 0;
	int key_value = 0;
	unsigned char led_state = LED_OFF;
	unsigned char beep_state = BEEP_OFF;

	clk_enable();		/* 使能所有的时钟 */
	led_init();			/* 初始化led 	*/
	beep_init();        /* 蜂鸣器初始化 */
	key_init();         /* 按键初始化 */
 
	while(1)			
	{	
		key_value = get_key_value();
		if(key_value)
		{
			switch ((key_value))
			{
				case KEY_PRESS:
					beep_state = !beep_state;
					led_state = !led_state;
					beep_controller(beep_state);
					led_controller(LED0, led_state);
					break;
			}
		}
		delay(10);
	}

	return 0;
}
