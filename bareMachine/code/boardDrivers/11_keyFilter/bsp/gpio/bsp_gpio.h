#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H
#include "imx6ul.h"
/***************************************************************
文件名	: 	 bsp_gpio.h
描述	   : GPIO操作文件头文件。
***************************************************************/

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

/*
 * GPIO中断触发类型枚举
 */
typedef enum _gpio_interrupt_mode
{
    GPIO_NO_INT_MODE                = 0U,   /* 无中断功能 */
    GPIO_INT_LOW_LEVEL              = 1U, 	/* 低电平触发	*/
    GPIO_INT_HIGH_LEVEL             = 2U, 	/* 高电平触发 */
    GPIO_INT_RISING_EDGE            = 3U, 	/* 上升沿触发	*/
    GPIO_INT_FALLING_EDGE           = 4U, 	/* 下降沿触发 */
    GPIO_INT_RISING_OR_FALLING_EDGE = 5U, 	/* 上升沿和下降沿都触发 */
} GPIO_interrupt_mode_t;	
	
typedef struct GPIO_Config
{
    GPIO_pin_direction direction;         /* GPIO方向:输入还是输出 */
    GPIO_output_level output_level;       /* 如果是输出的话，默认输出电平 */
    GPIO_interrupt_mode_t interrupt_mode; /* 中断方式 */
} GPIO_Config;

/*
 * @description	 : 读取指定GPIO的电平值 。
 * @param - base	 : 要读取的GPIO组。
 * @param - pin	 : 要读取的GPIO脚号。
 * @return 		 : 无
 */
extern int gpio_pin_read(GPIO_Type *gpio, int pin_index);

/*
 * @description	 : 指定GPIO输出高或者低电平 。
 * @param - base	 : 要输出的的GPIO组。
 * @param - pin	 : 要输出的GPIO脚号。
 * @param - value	 : 要输出的电平，1 输出高电平， 0 输出低低电平
 * @return 		 : 无
 */
extern void gpio_pin_write(GPIO_Type *gpio, int pin_index, int value);

/*
 * @description  			: 使能GPIO的中断功能
 * @param - base 			: 要使能的IO所在的GPIO组。
 * @param - pin  			: 要使能的GPIO在组内的编号。
 * @return		 			: 无
 */
extern void gpio_enable_interrput(GPIO_Type* base, unsigned int pin);

/*
 * @description  			: 禁止GPIO的中断功能
 * @param - base 			: 要禁止的IO所在的GPIO组。
 * @param - pin  			: 要禁止的GPIO在组内的编号。
 * @return		 			: 无
 */
extern void gpio_disable_interrput(GPIO_Type* base, unsigned int pin);

/*
 * @description  			: 清除中断标志位(写1清除)
 * @param - base 			: 要清除的IO所在的GPIO组。
 * @param - pin  			: 要清除的GPIO掩码。
 * @return		 			: 无
 */
extern void gpio_clear_interrput_flags(GPIO_Type* base, unsigned int pin);

/*
 * @description		: GPIO初始化。
 * @param - base	: 要初始化的GPIO组。
 * @param - pin		: 要初始化GPIO在组内的编号。
 * @param - config	: GPIO配置结构体。
 * @return 			: 无
 */
extern void gpio_pin_config(GPIO_Type *gpio, int pin_index, GPIO_Config *config);

#endif //_BSP_GPIO_H
