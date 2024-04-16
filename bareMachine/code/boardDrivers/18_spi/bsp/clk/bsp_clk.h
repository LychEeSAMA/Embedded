#ifndef _BSP_CLK_H
#define _BSP_CLK_H
/***************************************************************
文件名	: 	 bsp_clk.h
描述	   : 系统时钟驱动头文件。
***************************************************************/

#include "imx6ul.h"

/* 使能I.MX6U所有外设时钟 */
extern void imx6ull_clk_enable(void);

/* 初始化系统时钟，设置系统时钟为792Mhz */
extern void imx6ull_clk_init(void);

#endif //_BSP_CLK_H
