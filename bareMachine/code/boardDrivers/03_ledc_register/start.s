/*************************************
文件名	: 	 start.s
描述	   : ZERO-I.MX6UL/I.MX6ULL开发板启动文件，完成C环境初始化，
		    C环境初始化完成以后跳转到C代码。
*************************************/
.global _start

.global __bss_start
_bss_start:
    .word __bss_start
_bss_end:
    .word __bss_end

_start:
    /* 步骤1：进入svc模式 */
    mrs r0, cpsr     /* 将cpsr程序状态寄存器中的值读取到r0中 */
    bic r0, r0, #0x1f /* 将cpsr寄存器的低5位清0 */
    orr r0, r0, #0x13 /* 对cpsr寄存器的低5位进行赋值，进入svc模式 */
    msr cpsr, r0     /* 将赋值后的数据写入cpsr寄存器 */

    /* 步骤2：清除bss段 */
    ldr r0, _bss_start
    ldr r1, _bss_end
    mov r2, #0
bss_loop:
    stmia r0!, {r2} /* 向r0当前的地址写入 r2中的数据也就是0 然后r0地址自增 */
    cmp r0, r1      /* 如果r0的地址小于等于r1就继续循环清零 */
    ble bss_loop

    /* 步骤3：设置SP指针 */
    ldr sp, =0x80200000 /* 设置栈顶指针地址 */
    b main /* 跳转到c语言的main函数 */




