/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*					WIN32 PORT & LINUX PORT
*                          (c) Copyright 2004, Werner.Zimmermann@fht-esslingen.de
*                                           All Rights Reserved
*
*                                               EXAMPLE #0
*             Used to study the scheduling behaviour of the WIN32 and LINUX port during development
*********************************************************************************************************
*/

#undef NDEBUG
#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"
#include "debug.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define TASK_STK_SIZE 1024 // Stack size, in bytes

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
OS_STK TaskStartStk[TASK_STK_SIZE]; // Task stacks
OS_STK TaskReadKeyStk[TASK_STK_SIZE];
OS_STK Task1Stk[TASK_STK_SIZE];
OS_STK Task2Stk[TASK_STK_SIZE];

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void TaskStart(void *pdata); // The 3 tasks
void TaskReadKey(void *pdata);
void Task1(void *pdata);
void Task2(void *pdata);

/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/
int main(void)
{
    // Display a banner.
#ifdef __WIN32__
    printf("##### uCOS-II V%4.2f Port V%4.2f for WIN32 #####\n", ((FP32)OSVersion()) / 100, ((FP32)OSPortVersion()) / 100);
#endif
#ifdef __LINUX__
    printf("##### uCOS-II V%4.2f Port V%4.2f for LINUX #####\n", ((FP32)OSVersion()) / 100, ((FP32)OSPortVersion()) / 100);
#endif

    // Initialize uCOS-II.
    OSInit(); //Calling sequence -->OSInitHookBegin-->OSTaskStkInit-->OSTCBInitHook-->OSTaskCreateHook-->OSInitHookEnd

    // Create the first task
    OSTaskCreate(TaskStart, (void *)10, &TaskStartStk[TASK_STK_SIZE], 10); //Calling sequence -->OSTaskStkInit-->OSTCBInitHook-->OSTaskCreateHook

    // Start multitasking.
    OSStart(); //Calling sequence -->OSTaskSwHook-->OSStartHighRdy

    /* NEVER EXECUTED */
    printf("main(): This lines should never be executed\n");

    return 0;
}

/*
*********************************************************************************************************
*                                                First Task (startup task)
*********************************************************************************************************
*/
void TaskStart(void *pdata)
{
    OSTaskCreate(TaskReadKey, (void *)12, &TaskReadKeyStk[TASK_STK_SIZE], 12); //Create another tasks
    debug("TaskReadyKey created");

    OSTaskCreate(Task1, (void *)13, &Task1Stk[TASK_STK_SIZE], 13); //Create another tasks
    debug("Task1 created");

    OSTaskCreate(Task2, (void *)14, &Task2Stk[TASK_STK_SIZE], 14); //Create another tasks
    debug("Task2 created");
    

    while (1)
    {
        printf("%4u: ***** TaskStart *****\n", OSTime);
        OSTimeDly(1); //Calling sequence -->OSTaskSwHook-->OSCtxSw
        OSTaskSuspend(OS_PRIO_SELF);
    }
}


/*
*********************************************************************************************************
*                                                Task 1
*********************************************************************************************************
*/

void Task1(void *pdata)
{
    while (1)
    {
        printf("%4u: ***** Task1 *****\n", OSTime);
        OSTimeDly(4);
    }
}


/*
*********************************************************************************************************
*                                                Task 2
*********************************************************************************************************
*/
void Task2(void *pdata)
{
    while (1)
    {
        printf("%4u: ***** Task2 *****\n", OSTime);
        OSTimeDly(8);
    }
}


/*
*********************************************************************************************************
*                                                Third Task
*********************************************************************************************************
*/
void TaskReadKey(void *pdata)
{
    while (1)
    {
        printf("%4u: ***** TaskReadKey *****\n", OSTime);
        if (_kbhit())
        {
            exit(0);
        }
        OSTimeDly(2);
    }
}


