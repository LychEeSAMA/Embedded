#ifndef _BEEP_H
#define _BEEP_H

#include "imx6ul.h"

typedef enum
{
    BEEP_ON  = 0x00,
    BEEP_OFF = 0x01,
} BeepAction;

/* 蜂鸣器初始化 */
extern void beep_init(void);

/* 蜂鸣器控制 */
extern void beep_controller(BeepAction action);

#endif //_BEEP_H