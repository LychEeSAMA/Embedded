#ifndef _BSP_EXTI_H
#define _BSP_EXTI_H
/***************************************************************
文件名	: 	 bsp_exit.c
其他	   : 配置按键对应的GPIP为中断模式
***************************************************************/
#include "imx6ul.h"

/*
 * @description			: 初始化外部中断
 * @param				: 无
 * @return 				: 无
 */
extern void imx6ull_exti_key_init(void);

#endif //_BSP_EXTI_H
