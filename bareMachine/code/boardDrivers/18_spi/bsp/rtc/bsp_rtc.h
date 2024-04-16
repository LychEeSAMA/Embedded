#ifndef _BSP_RTC_H
#define _BSP_RTC_H
/***************************************************************
文件名	: 	 bsp_rtc.c
作者	   : 左忠凯
***************************************************************/
#include "imx6ul.h"

/* 相关宏定义 */	
#define SECONDS_IN_A_DAY 		(86400) /* 一天86400秒	 		*/
#define SECONDS_IN_A_HOUR 		(3600)	/* 一个小时3600秒 		*/
#define SECONDS_IN_A_MINUTE 	(60)	/* 一分钟60秒  		 	*/
#define DAYS_IN_A_YEAR 			(365)	/* 一年365天 			*/
#define YEAR_RANGE_START 		(1970)	/* 开始年份1970年 		*/
#define YEAR_RANGE_END 			(2099)	/* 结束年份2099年 		*/

/* 时间日期结构体 */	
struct rtc_datetime
{
    unsigned short year;  /* 范围为:1970 ~ 2099 		*/
    unsigned char month;  /* 范围为:1 ~ 12				*/
    unsigned char day;    /* 范围为:1 ~ 31 (不同的月，天数不同).*/
    unsigned char hour;   /* 范围为:0 ~ 23 			*/
    unsigned char minute; /* 范围为:0 ~ 59				*/
    unsigned char second; /* 范围为:0 ~ 59				*/
};

/*
 * @description : 初始化RTC
 * @return		: 无
 */
extern void imx6ull_rtc_init(void);

/*
 * @description		: 设置时间和日期
 * @param - datetime: 要设置的日期和时间
 * @return 			: 无
 */
extern void rtc_set_date_time(struct rtc_datetime *datetime);

/*
 * @description		: 获取当前时间
 * @param - datetime: 获取到的时间，日期等参数
 * @return 			: 无
 */
extern void rtc_get_date_time(struct rtc_datetime *datetime);

#endif
