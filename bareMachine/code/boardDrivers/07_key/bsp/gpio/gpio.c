#include "gpio.h"

/* 读取指定gpio的值 */
int gpio_pin_read(GPIO_Type *gpio, int pin_index)
{
    return ((gpio->DR >> pin_index) & 0x01);
}

/* 向指定gpio写入数据 */
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

/* gpio 配置 主要是设置gpio是做输入还是做输出 */
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
}
