#ifndef _BSP_DELAY_H
#define _BSP_DELAY_H
/***************************************************************
文件名	: 	 bsp_delay.h
描述	   : 延时头文件。
***************************************************************/
#include "imx6ul.h"

/*
 * @description		: 微秒(us)级延时
 * @param - value	: 需要延时的us数,最大延时0XFFFFFFFFus
 * @return 			: 无
 */
extern void delay_us(unsigned int usdelay);

/*
 * @description		: 毫秒(ms)级延时
 * @param - msdelay	: 需要延时的ms数
 * @return 			: 无
 */
extern void delay_ms(unsigned int msdelay);

/*
 * @description	: 延时函数,在396Mhz的主频下
 * 			  	  延时时间大约为1ms
 * @param - n	: 要延时的ms数
 * @return 		: 无
 */
extern void delay(volatile unsigned int n);

/*
 * @description	: 延时有关硬件初始化,主要是GPT定时器
				  GPT定时器时钟源选择ipg_clk=66Mhz
 * @param		: 无
 * @return 		: 无
 */
extern void imx6ull_delay_init(void);

#endif //_BSP_DELAY_H

