/********************************************************************************
* @File name: main.c
* @Author: twei
* @Version: 1.0
* @Date: 2024-05-05
* @Description: 用于测试循环队列功能
* @history: 无 
********************************************************************************/

#include <stdio.h>
#include "seqQueue.h"

static void SeqQueueTask1(void)
{
    printf("[%s] Do task!\n", __FUNCTION__);
}

static void SeqQueueTask2(void)
{
    printf("[%s] Do task!\n", __FUNCTION__);
}

static void SeqQueueTask3(void)
{
    printf("[%s] Do task!\n", __FUNCTION__);
}

static void SeqQueueTask4(void)
{
    printf("[%s] Do task!\n", __FUNCTION__);
}

static void (* TaskArray[5])(void) = { 
    SeqQueueTask1,
    SeqQueueTask2,
    SeqQueueTask3,
    SeqQueueTask4,
};

int main(int argc, char const *argv[])
{
    printf("Queue test start! Complie at time:[%s]\n", __TIME__);

    SeqQueue *sq = SeqQueueInit();
    if (NULL == sq)
    {
        printf("[%s] Seq queue init faild\n", __FUNCTION__);
        return 1;
    }
    printf("sq->front:[%d]\n", sq->front);
    printf("sq->rear:[%d]\n", sq->rear);

    for (size_t i = 0; i < 4; i++)
    {
        EnSeqQueue(sq, i, TaskArray[i]);
    }
    SeqQueueDump(sq);
    
    for (size_t i = 0; i < 3; i++)
    {
        OutSeqQueue(sq);
    }
    SeqQueueDump(sq);

    for (size_t i = 1; i < 3; i++)
    {
        EnSeqQueue(sq, i*10, TaskArray[i]);
    }
    SeqQueueDump(sq);


    return 0;
}
