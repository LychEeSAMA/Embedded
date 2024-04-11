#include "bsp_key.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"
/***************************************************************
文件名	: 	 bsp_key.h
描述	   : 按键驱动文件。
***************************************************************/

/*!
 * @note NXP官方提供了操作寄存器地址的函数接口与对应寄存器的宏定义，这就让我们可以快速的进行寄存器配置
 *       一个外设使用的流程一般如为：1.使能外设时钟-->2.设置引脚的功能复用(复用为GPIO或I2C_SCL等)-->3.配置复用后引脚的电器属性
 *       -->4.设置引脚做输入或输出-->5.向DR寄存器写入数据
 * 		 在配置引脚电器属性时 做输出的引脚和做输入的引脚会略有不同 但是大同小异
 */

/*
 * @description	: 初始化按键
 * @param 		: 无
 * @return 		: 无
 */
void key_init(void)
{	
	GPIO_Config key_config;
	
	/* 1、初始化IO复用, 复用为GPIO1_IO18 */
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);

	/* 2、、配置UART1_CTS_B的IO属性	
	 *bit 16:0 HYS关闭
	 *bit [15:14]: 11 默认22K上拉
	 *bit [13]: 1 pull功能
	 *bit [12]: 1 pull/keeper使能
	 *bit [11]: 0 关闭开路输出
	 *bit [7:6]: 10 速度100Mhz
	 *bit [5:3]: 000 关闭输出
	 *bit [0]: 0 低转换率
	 */
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);
	
	/* 3、初始化GPIO */
	//GPIO1->GDIR &= ~(1 << 18);	/* GPIO1_IO18设置为输入 */	
	key_config.direction = GPIO_INPUT;
	gpio_pin_config(GPIO1, 18, &key_config);
	
}

/* 获取按键的gpio值 0按下 1释放 */
static int get_cur_key_value(void)
{
    int ret = KEY_RELEASE;
    ret = gpio_pin_read(GPIO1, 18);
    return ret;    
}

/*
 * @description	: 获取按键值 
 * @param 		: 无
 * @return 		: 0 没有按键按下，其他值:对应的按键值
 */
int key_get_value(void)
{
	int ret = 0;
	static unsigned char release = 1; /* 按键松开 */

	if ((1 == release) && (0 == get_cur_key_value())) /* KEY0 	*/
	{
		delay(10);	 /* 延时消抖 		*/
		release = 0; /* 标记按键按下 */
		if (0 == get_cur_key_value())
			ret = KEY_PRESS;
	}
	else if (1 == get_cur_key_value())
	{
		ret = KEY_RELEASE;
		release = 1; /* 标记按键释放 */
	}

	return ret;
}
