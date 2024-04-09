/**************************************************************
文件名	    :led.s
作者	   : twei
版本	   : V1.0
描述	   : 裸机实验1 汇编点灯
			 使用汇编来点亮开发板上的LED灯,学习和掌握如何用汇编语言来
			 完成对I.MX6U处理器的GPIO初始化和控制。
时间	   : 2024.04.09
**************************************************************/
.global _start

_start:
    /* 
        步骤1:初始化外设时钟
        从IMX6ULL参考手册第18章CCM的介绍中得知,CCM_CCGR0-CCM_CCGR6控制所有外设的时钟
        其中CCM_CCGR2的bit27-26控制gpio3的时钟使能,但此处为了方便,不单独初始化gpio3,选择初始化所有外设时钟
        初始化赋值使用ARM体系中的R0和R1寄存器
    */
    ldr R0, =0x020C4068     /* CCGR0 */
    ldr R1, =0XFFFFFFFF 
    str R1, [R0]

    ldr r0, =0X020C406C  	/* CCGR1 */
	str r1, [r0]

	ldr r0, =0X020C4070  	/* CCGR2 */
	str r1, [r0]
	
	ldr r0, =0X020C4074  	/* CCGR3 */
	str r1, [r0]
	
	ldr r0, =0X020C4078  	/* CCGR4 */
	str r1, [r0]
	
	ldr r0, =0X020C407C  	/* CCGR5 */
	str r1, [r0]
	
	ldr r0, =0X020C4080  	/* CCGR6 */
	str r1, [r0]

    /* 
        步骤2:配置gpio的管脚复用,点灯用的LED0连接在GPIO01的io3上
        此处需要将GPIO01的io3复用为gpio
        ps:SW_MUX为Software_Multiplexer
    */
    ldr r0, =0X020E0068	/* 将寄存器SW_MUX_GPIO1_IO03_BASE加载到r0中 */
	ldr r1, =0X5		/* 
                            设置寄存器SW_MUX_GPIO1_IO03_BASE的MUX_MODE为5
                            0101 ALT5 — Select mux mode: ALT5 mux port: 
                            GPIO1_IO03 of instance: gpio1 
                        */
	str r1, [r0]

    /* 
        步骤3:设置GPIO1_IO03的电器属性
        bit 16:0 HYS关闭
        bit [15:14]: 00 默认下拉
        bit [13]: 0 kepper功能
        bit [12]: 1 pull/keeper使能
        bit [11]: 0 关闭开路输出
        bit [7:6]: 10 速度100Mhz
        bit [5:3]: 110 R0/6驱动能力
        bit [0]: 0 低转换率
    */
    /* 寄存器SW_PAD_GPIO1_IO03_BASE */
    ldr r0, =0X020E02F4	
    ldr r1, =0X10B0
    str r1, [r0]

	/* 设置GPIO1_IO03为输出 */
    ldr r0, =0X0209C004	/*寄存器GPIO1_GDIR */
    ldr r1, =0X0000008		
    str r1, [r0]

	/* 5、打开LED0
	 * 从原理图得知需要设置GPIO1_IO03输出低电平 LED才会亮
	 */
	ldr r0, =0X0209C000	/*寄存器GPIO1_DR */
    ldr r1, =0		
    str r1, [r0]

/* 死循环保持LED0常亮 */
loop:
	b loop 
     	