#ifndef _BSP_KEY_KEY_H_
#define _BSP_KEY_KEY_H_

typedef enum keyState
{
    KEY_PRESS   = 0x01,
    KEY_RELEASE = 0x00
} keyState;

/* 按键初始化 */
extern void key_init(void);

/* 获取消抖后的按键值 */
extern int get_key_value(void);

#endif //_BSP_KEY_KEY_H_