#ifndef _BSP_INTERRPUT_H
#define _BSP_INTERRPUT_H
#include "imx6ul.h"
/***************************************************************
文件名	: 	 bsp_gpio.h
描述	   : GPIO操作文件头文件。
***************************************************************/

/* 定义中断处理回调函数 */
typedef void (*system_irq_handler)(unsigned int giccIar, void *param);

typedef struct sys_irq_handle
{
    system_irq_handler irqHandler;
    void *userParam;
} system_irq_handle_t;

/*
 * @description			: 给指定的中断号注册中断服务函数 
 * @param - irq			: 要注册的中断号
 * @param - handler		: 要注册的中断处理函数
 * @param - usrParam	: 中断服务处理函数参数
 * @return 				: 无
 */
extern void system_register_irq_handler(IRQn_Type irq, system_irq_handler handler, void *userParam);

/*
 * @description	: 中断初始化函数
 * @param		: 无
 * @return 		: 无
 */
extern void imx6ull_interrput_init(void);

#endif //_BSP_INTERRPUT_H
