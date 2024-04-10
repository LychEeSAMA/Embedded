.global _start  		

/*
 * 描述： _start函数，程序从此函数开始执行，此函数主要功能是设置C
 *		 运行环境。
 */
_start:

	/* 进入SVC模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 	*/
	orr r0, r0, #0x13 	/* r0或上0x13,表示使用SVC模式					*/
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 					*/

	/* 
		因为 I.MX6U-ALPHA 开发 板 上 的 DDR3 地 址 范 围 是 0X80000000~0XA0000000(512MB)
		Cortex-A7 的堆栈是向下增长的，所以将 SP 指针设置为 0X80200000，
		因此 SVC 模式的栈大小 0X80200000-0X80000000=0X200000=2MB
	*/
	ldr sp, =0X80200000	/* 设置栈指针			 */
	b main				/* 跳转到main函数 		 */

