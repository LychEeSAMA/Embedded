#ifndef _BSP_LCD_H
#define _BSP_LCD_H
/***************************************************************
文件名	: 	 bsp_lcd.h
描述	   : LCD驱动文件头文件。
***************************************************************/
#include "imx6ul.h"

/* 颜色 */
#define LCD_BLUE		  0x000000FF
#define LCD_GREEN		  0x0000FF00
#define LCD_RED 		  0x00FF0000
#define LCD_CYAN		  0x0000FFFF
#define LCD_MAGENTA 	  0x00FF00FF
#define LCD_YELLOW		  0x00FFFF00
#define LCD_LIGHTBLUE	  0x008080FF
#define LCD_LIGHTGREEN	  0x0080FF80
#define LCD_LIGHTRED	  0x00FF8080
#define LCD_LIGHTCYAN	  0x0080FFFF
#define LCD_LIGHTMAGENTA  0x00FF80FF
#define LCD_LIGHTYELLOW   0x00FFFF80
#define LCD_DARKBLUE	  0x00000080
#define LCD_DARKGREEN	  0x00008000
#define LCD_DARKRED 	  0x00800000
#define LCD_DARKCYAN	  0x00008080
#define LCD_DARKMAGENTA   0x00800080
#define LCD_DARKYELLOW	  0x00808000
#define LCD_WHITE		  0x00FFFFFF
#define LCD_LIGHTGRAY	  0x00D3D3D3
#define LCD_GRAY		  0x00808080
#define LCD_DARKGRAY	  0x00404040
#define LCD_BLACK		  0x00000000
#define LCD_BROWN		  0x00A52A2A
#define LCD_ORANGE		  0x00FFA500
#define LCD_TRANSPARENT   0x00000000

/* 屏幕ID */
#define ATK4342		0X4342	/* 4.3寸480*272 	*/
#define ATK4384		0X4384	/* 4.3寸800*480 	*/
#define ATK7084		0X7084	/* 7寸800*480 		*/
#define ATK7016		0X7016	/* 7寸1024*600 		*/
#define ATK1018		0X1018	/* 10.1寸1280*800 	*/

/* LCD显存地址 */
#define LCD_FRAMEBUF_ADDR	(0x89000000)

/* LCD控制参数结构体 */
struct tftlcd_typedef{
	unsigned short height;		/* LCD屏幕高度 */
	unsigned short width;		/* LCD屏幕宽度 */
	unsigned char pixsize;		/* LCD每个像素所占字节大小 */
	unsigned short vspw;
	unsigned short vbpd;
	unsigned short vfpd;
	unsigned short hspw;
	unsigned short hbpd;
	unsigned short hfpd;
	unsigned int framebuffer; 	/* LCD显存首地址   	  */
	unsigned int forecolor;		/* 前景色 */
	unsigned int backcolor;		/* 背景色 */
};

extern struct tftlcd_typedef tftlcd_dev;

/*
 * @description	: 始化LCD
 * @param 		: 无
 * @return 		: 无
 */
extern void imx6ull_lcd_init(void);

/*
 * @description		: 画点函数 
 * @param - x		: x轴坐标
 * @param - y		: y轴坐标
 * @param - color	: 颜色值
 * @return 			: 无
 */
extern inline void lcd_draw_point(unsigned short x, unsigned short y, unsigned int color);

/*
 * @description		: 读取指定点的颜色值
 * @param - x		: x轴坐标
 * @param - y		: y轴坐标
 * @return 			: 读取到的指定点的颜色值
 */
extern inline unsigned int lcd_read_point(unsigned short x,unsigned short y);

/*
 * @description		: 以指定的颜色填充一块矩形
 * @param - x0		: 矩形起始点坐标X轴
 * @param - y0		: 矩形起始点坐标Y轴
 * @param - x1		: 矩形终止点坐标X轴
 * @param - y1		: 矩形终止点坐标Y轴
 * @param - color	: 要填充的颜色
 * @return 			: 读取到的指定点的颜色值
 */
extern void lcd_fill(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned int color);

/*
 * @description		: 清屏
 * @param - color	: 颜色值
 * @return 			: 读取到的指定点的颜色值
 */
extern void lcd_clear(unsigned int color);

#endif
