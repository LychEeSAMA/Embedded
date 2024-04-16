#ifndef _BSP_SPI_H
#define _BSP_SPI_H
/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 bsp_spi.h
作者	   : 左忠凯
版本	   : V1.0
描述	   : SPI驱动头文件。
其他	   : 无
论坛 	   : www.wtmembed.com
日志	   : 初版V1.0 2019/1/17 左忠凯创建
***************************************************************/
#include "imx6ul.h"

/*
 * @description		: 初始化SPI
 * @param - base	: 要初始化的SPI
 * @return 			: 无
 */
extern void imx6ull_spi_init(ECSPI_Type *base);

/*
 * @description		: SPI通道0发送/接收一个字节的数据
 * @param - base	: 要使用的SPI
 * @param - txdata	: 要发送的数据
 * @return 			: 无
 */
extern unsigned char spich0_read_write_byte(ECSPI_Type *base, unsigned char txdata);

#endif

