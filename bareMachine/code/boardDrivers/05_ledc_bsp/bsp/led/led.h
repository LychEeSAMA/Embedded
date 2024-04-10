#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "imx6ul.h"
/***************************************************************
版本	   : V1.0
描述	   : LED驱动头文件。
其他	   : 无
***************************************************************/

typedef enum led_ID
{
    LED0  = 0x00, 
    LED1  = 0x01  
}Led_ID;

typedef enum led_action
{
    LED_ON  = 0x01, /* 打开led */
    LED_OFF = 0x00  /* 关闭led */
}Led_Action;

/* 函数声明 */
extern void led_init(void);

/* led控制器 */
extern void led_controller(Led_ID led, Led_Action action);
#endif

