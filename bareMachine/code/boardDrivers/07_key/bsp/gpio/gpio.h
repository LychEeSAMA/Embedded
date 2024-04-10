#ifndef _BSP_GPIO_GPIO_H_
#define _BSP_GPIO_GPIO_H_

#include "bsp_common.h"

/* gpio输入输出模式 */
typedef enum GPIO_pin_direction
{
    GPIO_INPUT  = 0U,  	/* 输入 */
    GPIO_OUTPUT = 1U    /* 输出 */
} GPIO_pin_direction;

/* gpio电平高低 */
typedef enum GPIO_output_level
{
    GPIO_LEVLE_HIGH = 1U,  	/* 高电平 */
    GPIO_LEVLE_LOW  = 0U    /* 低电平 */
} GPIO_output_level;
	
typedef struct GPIO_Config
{
    GPIO_pin_direction direction;     /* GPIO方向:输入还是输出 */
    GPIO_output_level output_level;   /* 如果是输出的话，默认输出电平 */
} GPIO_Config;

/* 读取指定gpio的值 */
extern int gpio_pin_read(GPIO_Type *gpio, int pin_index);

/* 向指定gpio写入数据 */
extern void gpio_pin_write(GPIO_Type *gpio, int pin_index, int value);

/* gpio 配置 */
extern void gpio_pin_config(GPIO_Type *gpio, int pin_index, GPIO_Config *config);

#endif //_BSP_GPIO_GPIO_H_