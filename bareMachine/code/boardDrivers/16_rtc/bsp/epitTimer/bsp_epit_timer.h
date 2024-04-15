#ifndef _BSP_EPIT_TIMER_H
#define _BSP_EPIT_TIMER_H
#include "imx6ul.h"


/*
 * @description		: 初始化EPIT定时器.
 *					  EPIT定时器是32位向下计数器,时钟源使用ipg=66Mhz		 
 * @param - frac	: 分频值，范围为0~4095，分别对应1~4096分频。
 * @param - value	: 延时时长(ms)
 * @return 			: 无
 */
extern void imx6ull_epit1_timer_init(unsigned int frac, unsigned int delay);


#endif //_BSP_EPIT_TIMER_H