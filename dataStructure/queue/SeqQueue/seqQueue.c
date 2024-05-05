/********************************************************************************
* @File name: seqQueue.c
* @Author: twei
* @Version: 1.0
* @Date: 2024-05-05
* @Description: 此文件实现了循环队列相关操作，仅供学习参考
* @history: 无 
********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include "seqQueue.h"

/*!
 * @brief 循环队列初始化
 * @param 无  
 * @return 返回初始化好的队列地址
 */
SeqQueue *SeqQueueInit(void)
{
    SeqQueue *sq = (SeqQueue *)calloc(1, sizeof(SeqQueue));
    if (NULL == sq)
    {
        printf("[%s] Queue init faild\n", __FUNCTION__);
        return NULL;
    }

    sq->front = 0;
    sq->rear = 0;
    sq->maxSize = MAX_SIZE;

    return sq;
}

/*!
 * @brief 循环队列初始化
 * @param sq 队列对象指针  
 * @return 见SEQ_QUEUE_STATE描述
 */
SEQ_QUEUE_STATE SeqQueueGetState(SeqQueue *sq)
{
    if (NULL == sq)
    {
        printf("[%s] Invaild param!\n", __FUNCTION__);
        return SEQ_QUEUE_INVAILD;
    }

    /* 队满 */
    if (((sq->rear + 1) % sq->maxSize) == sq->front)
        return SEQ_QUEUE_FULL;
    /* 队空 */
    else if (sq->front == sq->rear)
        return SEQ_QUEUE_EMPTY;
    else 
        return SEQ_QUEUE_NOT_EMPTY;
} 

/*!
 * @brief 入队
 * @param sq 队列对象指针  
 * @param data 要保存的数据 
 * @param func 队列任务函数 
 * @return 见SEQ_QUEUE_STATE描述
 */
SEQ_QUEUE_STATE EnSeqQueue(SeqQueue *sq, int data, SeqQueueWorkFunc func)
{   
    if (NULL == sq)
    {
        printf("[%s] Param is invaild!\n", __FUNCTION__);
        return SEQ_QUEUE_FAILED;
    }
    
    if (SEQ_QUEUE_FULL == SeqQueueGetState(sq))
    {
        printf("[%s] Seq queue is full!\n", __FUNCTION__);
        return SEQ_QUEUE_FAILED;
    }

    sq->rear = (sq->rear + 1) % sq->maxSize;
    sq->task[sq->rear].data = data;
    sq->task[sq->rear].func = func;

    return SEQ_QUEUE_SUCCESS;
}

/*!
 * @brief 出队
 * @param sq 队列对象指针  
 * @return 见SEQ_QUEUE_STATE描述
 */
SEQ_QUEUE_STATE OutSeqQueue(SeqQueue *sq)
{   
    if (NULL == sq)
    {
        printf("[%s] Param is invaild!\n", __FUNCTION__);
        return SEQ_QUEUE_FAILED;
    }
    
    if (SEQ_QUEUE_EMPTY == SeqQueueGetState(sq))
    {
        printf("[%s] Seq queue is empty! Can't out queue!\n", __FUNCTION__);
        return SEQ_QUEUE_FAILED;
    }

    sq->front = (sq->front + 1) % sq->maxSize;
    
    printf("[%s] Current queue node index:[%d]\n", __FUNCTION__, sq->front);
    /* 出队时执行注册的回调函数以完成任务 */
    if (NULL != sq->task[sq->front].func)
        sq->task[sq->front].func();

    sq->task[sq->front].data = -1;
    sq->task[sq->front].func = NULL;

    return SEQ_QUEUE_SUCCESS;
}

/*!
 * @brief 队列数据dump
 * @param sq 队列对象指针  
 * @return 无
 */
void SeqQueueDump(SeqQueue *sq)
{
    if (NULL == sq)
    {
        printf("[%s] Param is invaild!\n", __FUNCTION__);
        return;
    }

    printf("====================================================\n");
    int i = 0;
    for (i = sq->front; i != sq->rear; i = (i + 1) % sq->maxSize)
    {
        if (sq->task[i].data != -1)
            printf("index:[%d] data:[%d]\n", i, sq->task[i].data);
    }
    if (sq->task[i].data != -1)
        printf("index:[%d] data:[%d]\n", i, sq->task[i].data);

    printf("sq->front:[%d] sq->rear:[%d] element number:[%d]\n", sq->front, sq->rear, abs(sq->front - sq->rear));
    printf("====================================================\n");
}
