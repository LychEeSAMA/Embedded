#ifndef _BSP_UART_H
#define _BSP_UART_H

#include "imx6ul.h"

/*
 * @description : 发送一个字符
 * @param - c	: 要发送的字符
 * @return		: 无
 */
extern void putc(unsigned char c);

/*
 * @description : 发送一个字符串
 * @param - str	: 要发送的字符串
 * @return		: 无
 */
extern void puts(char *str);

/*
 * @description : 接收一个字符
 * @param 		: 无
 * @return		: 接收到的字符
 */
extern unsigned char getc(void);

/*
 * @description : 初始化串口1,波特率为115200
 * @param		: 无
 * @return		: 无
 */
extern void imx6ull_uart_init(void);

#endif //_BSP_UART_H 