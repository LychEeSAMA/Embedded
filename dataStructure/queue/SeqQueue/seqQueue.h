/********************************************************************************
* @File name: seqQueue.h
* @Author: twei
* @Version: 1.0
* @Date: 2024-05-05
* @Description: 声明了循环队列的操作接口
* @history: 无 
********************************************************************************/

#ifndef _SEQ_QUEUE_H_
#define _SEQ_QUEUE_H_

#define MAX_SIZE 5

typedef void (* SeqQueueWorkFunc)(void);

typedef enum
{
    SEQ_QUEUE_EMPTY     = 0x00U, /* 队列空 */
    SEQ_QUEUE_NOT_EMPTY = 0X01U, /* 队列中有（0-MAX_SIZE-1）个元素 */
    SEQ_QUEUE_FULL      = 0x02U, /* 队列满 */
    SEQ_QUEUE_INVAILD   = 0x03U, /* 队列操作异常 */
    SEQ_QUEUE_SUCCESS   = 0x04U, /* 操作成功 */
    SEQ_QUEUE_FAILED    = 0x05U  /* 操作失败 */
} SEQ_QUEUE_STATE;

typedef struct 
{
    int data;
    SeqQueueWorkFunc func;
} SeqQueueTask;

typedef struct 
{
    SeqQueueTask task[MAX_SIZE];
    int front;
    int rear;
    int maxSize;
} SeqQueue;

/*!
 * @brief 循环队列初始化
 * @param 无  
 * @return 返回初始化好的队列地址
 */
extern SeqQueue *SeqQueueInit(void);

/*!
 * @brief 循环队列初始化
 * @param sq 队列对象指针  
 * @return 见SEQ_QUEUE_STATE描述
 */
extern SEQ_QUEUE_STATE SeqQueueGetState(SeqQueue *sq);

/*!
 * @brief 入队
 * @param sq 队列对象指针  
 * @param data 要保存的数据 
 * @param func 队列任务函数 
 * @return 见SEQ_QUEUE_STATE描述
 */
extern SEQ_QUEUE_STATE EnSeqQueue(SeqQueue *sq, int data, SeqQueueWorkFunc func);

/*!
 * @brief 出队
 * @param sq 队列对象指针  
 * @return 见SEQ_QUEUE_STATE描述
 */
extern SEQ_QUEUE_STATE OutSeqQueue(SeqQueue *sq);

/*!
 * @brief 队列数据dump
 * @param sq 队列对象指针  
 * @return 无
 * @remark 调试用
 */
extern void SeqQueueDump(SeqQueue *sq);

#endif //_SEQ_QUEUE_H_