#ifndef _BSP_BEEP_H
#define _BSP_BEEP_H
/***************************************************************
文件名	: 	 bsp_beep.h
描述	   : 蜂鸣器驱动头文件。
***************************************************************/
#include "imx6ul.h"

typedef enum
{
    BEEP_ON  = 0x00,
    BEEP_OFF = 0x01,
} BeepAction;

/* 蜂鸣器初始化 */
extern void imx6ull_beep_init(void);

/* 蜂鸣器控制 */
extern void beep_controller(BeepAction action);

#endif //_BSP_BEEP_H

