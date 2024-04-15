#include "bsp_gpio.h"
/***************************************************************
文件名	: 	 bsp_gpio.h
描述	   : GPIO操作文件。
***************************************************************/

/*
 * @description	 : 读取指定GPIO的电平值 。
 * @param - base	 : 要读取的GPIO组。
 * @param - pin	 : 要读取的GPIO脚号。
 * @return 		 : 无
 */
int gpio_pin_read(GPIO_Type *gpio, int pin_index)
{
    return ((gpio->DR >> pin_index) & 0x01);
}

/*
 * @description	 : 指定GPIO输出高或者低电平 。
 * @param - base	 : 要输出的的GPIO组。
 * @param - pin	 : 要输出的GPIO脚号。
 * @param - value	 : 要输出的电平，1 输出高电平， 0 输出低低电平
 * @return 		 : 无
 */
void gpio_pin_write(GPIO_Type *gpio, int pin_index, int value)
{
    switch (value)
    {
    case GPIO_LEVLE_HIGH:
        gpio->DR |= (1 << pin_index);
        break;
    
    case GPIO_LEVLE_LOW:
        gpio->DR &= ~(1 << pin_index);
        break;
    
    default:
        break;
    }
}

/*
 * @description  			: 使能GPIO的中断功能
 * @param - base 			: 要使能的IO所在的GPIO组。
 * @param - pin  			: 要使能的GPIO在组内的编号。
 * @return		 			: 无
 */
void gpio_enable_interrput(GPIO_Type* base, unsigned int pin)
{ 
    base->IMR |= (1 << pin);
}

/*
 * @description  			: 禁止GPIO的中断功能
 * @param - base 			: 要禁止的IO所在的GPIO组。
 * @param - pin  			: 要禁止的GPIO在组内的编号。
 * @return		 			: 无
 */
void gpio_disable_interrput(GPIO_Type* base, unsigned int pin)
{ 
    base->IMR &= ~(1 << pin);
}

/*
 * @description  			: 清除中断标志位(写1清除)
 * @param - base 			: 要清除的IO所在的GPIO组。
 * @param - pin  			: 要清除的GPIO掩码。
 * @return		 			: 无
 */
void gpio_clear_interrput_flags(GPIO_Type* base, unsigned int pin)
{
    base->ISR |= (1 << pin);
}

/*
 * @description  			: 设置GPIO的中断配置功能
 * @param - base 			: 要配置的IO所在的GPIO组。
 * @param - pin  			: 要配置的GPIO脚号。
 * @param - pinInterruptMode: 中断模式，参考枚举类型gpio_interrupt_mode_t
 * @return		 			: 无
 */
static void gpio_interrput_config(GPIO_Type* base, unsigned int pin, GPIO_interrupt_mode_t pin_int_mode)
{
	volatile uint32_t *icr;
	uint32_t icrShift;

	icrShift = pin;
	
	base->EDGE_SEL &= ~(1U << pin);

	if(pin < 16) 	/* 低16位 */
	{
		icr = &(base->ICR1);
	}
	else			/* 高16位 */
	{
		icr = &(base->ICR2);
		icrShift -= 16;
	}

	switch(pin_int_mode)
	{
		case(GPIO_INT_LOW_LEVEL):
			*icr &= ~(3U << (2 * icrShift));
			break;
		case(GPIO_INT_HIGH_LEVEL):
			*icr = (*icr & (~(3U << (2 * icrShift)))) | (1U << (2 * icrShift));
			break;
		case(GPIO_INT_RISING_EDGE):
			*icr = (*icr & (~(3U << (2 * icrShift)))) | (2U << (2 * icrShift));
			break;
		case(GPIO_INT_FALLING_EDGE):
			*icr |= (3U << (2 * icrShift));
			break;
		case(GPIO_INT_RISING_OR_FALLING_EDGE):
			base->EDGE_SEL |= (1U << pin);
			break;
		default:
			break;
	}
}

/*
 * @description		: GPIO初始化。
 * @param - base	: 要初始化的GPIO组。
 * @param - pin		: 要初始化GPIO在组内的编号。
 * @param - config	: GPIO配置结构体。
 * @return 			: 无
 */
void gpio_pin_config(GPIO_Type *gpio, int pin_index, GPIO_Config *config)
{
    switch (config->direction)
    {
    case GPIO_INPUT:
        gpio->GDIR &= ~(1 << pin_index);
        break;
    
    case GPIO_OUTPUT:
        gpio->GDIR |= (1 << pin_index);
        gpio_pin_write(gpio, pin_index, config->output_level);
        break;

    default:
        break;
    }
    /* 中断功能配置 */
    gpio_interrput_config(gpio, pin_index, config->interrupt_mode);
}




