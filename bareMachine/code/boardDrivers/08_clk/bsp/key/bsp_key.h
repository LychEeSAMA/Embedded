#ifndef _BSP_KEY_H
#define _BSP_KEY_H
#include "imx6ul.h"
/***************************************************************
文件名	: 	 bsp_key.h
描述	   : 按键驱动头文件。
***************************************************************/

typedef enum keyState
{
    KEY_PRESS   = 0x01,
    KEY_RELEASE = 0x00
} keyState;

/* 按键初始化 */
extern void key_init(void);

/* 获取消抖后的按键值 */
extern int key_get_value(void);

#endif //_BSP_KEY_H
