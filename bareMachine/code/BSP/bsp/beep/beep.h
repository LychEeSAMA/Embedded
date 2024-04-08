#ifndef _BSP_BEEP_H_
#define _BSP_BEEP_H_

typedef enum
{
    BEEP_ON  = 0x00,
    BEEP_OFF = 0x01,
} BeepAction;

/* 蜂鸣器初始化 */
extern void beep_init(void);

/* 蜂鸣器控制 */
extern void beep_controller(BeepAction action);

#endif //_BSP_BEEP_H_