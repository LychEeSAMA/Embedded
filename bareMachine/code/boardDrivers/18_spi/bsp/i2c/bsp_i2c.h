#ifndef _BSP_I2C_H
#define _BSP_I2C_H
/***************************************************************
文件名	: 	 bsp_i2c.c
描述	   : IIC驱动文件。
***************************************************************/
#include "imx6ul.h"

/* 相关宏定义 */
#define I2C_STATUS_OK				(0)
#define I2C_STATUS_BUSY				(1)
#define I2C_STATUS_IDLE				(2)
#define I2C_STATUS_NAK				(3)
#define I2C_STATUS_ARBITRATIONLOST	(4)
#define I2C_STATUS_TIMEOUT			(5)
#define I2C_STATUS_ADDRNAK			(6)

/*
 * I2C方向枚举类型
 */
enum i2c_direction
{
    kI2C_Write = 0x0, 		/* 主机向从机写数据 */
    kI2C_Read = 0x1,  		/* 主机从从机读数据 */
} ;

/*
 * 主机传输结构体
 */
struct i2c_transfer
{
    unsigned char slaveAddress;      	/* 7位从机地址 			*/
    enum i2c_direction direction; 		/* 传输方向 			*/
    unsigned int subaddress;       		/* 寄存器地址			*/
    unsigned char subaddressSize;    	/* 寄存器地址长度 			*/
    unsigned char *volatile data;    	/* 数据缓冲区 			*/
    volatile unsigned int dataSize;  	/* 数据缓冲区长度 			*/
};

/*
 * @description		: 初始化I2C，波特率100KHZ
 * @param - base 	: 要初始化的IIC设置
 * @return 			: 无
 */
extern void imx6ull_i2c_init(I2C_Type *base);

/*
 * @description	: I2C数据传输，包括读和写
 * @param - base: 要使用的IIC
 * @param - xfer: 传输结构体
 * @return 		: 传输结果,0 成功，其他值 失败;
 */
extern unsigned char i2c_master_transfer(I2C_Type *base, struct i2c_transfer *xfer);

#endif
