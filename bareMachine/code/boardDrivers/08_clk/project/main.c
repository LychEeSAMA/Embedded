#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	int i = 0;
	int keyvalue = 0;
	unsigned char led_state = OFF;
	unsigned char beep_state = OFF;

	imx6u_clk_init();	/* 初始化系统时钟 */
	clk_enable();		/* 使能所有的时钟 */
	led_init();			/* 初始化led */
	beep_init();		/* 初始化beep */
	key_init();			/* 初始化key */

	while(1)			
	{	
		keyvalue = key_get_value();
		if(keyvalue)
		{
			switch ((keyvalue))
			{
				case KEY_PRESS:
					beep_state = !beep_state;
					beep_controller(beep_state);
					break;
			}
		}
		i++;
		if(i==50)
		{
			i = 0;
			led_state = !led_state;
			led_controller(LED0, led_state);
		}

		delay(10);
	}

	return 0;
}
