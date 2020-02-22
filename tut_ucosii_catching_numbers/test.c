/*
*********************************************************************************************************
*                                          CME 332 Real Time Computing
*                                Department of Electrical and Computer Engineering
*                                          University of Saskatchewan
*
*                        Catching the Numbers Template for uC/OS-II WIN32 PORT & LINUX PORT
*
*                          (c) Copyright 2020, All Rights Reserved. Daniel. H. Y. Teng
*                                                                                         
*********************************************************************************************************
*/
#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"
#include "debug.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define TASK_STK_SIZE 512 // Size of each task's stacks (# of WORDs)

#define TaskStartPrio 1
#define TaskScanKeyPrio 10
#define TaskDisplayPrio 9
#define TaskElapsedPrio 2

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK TaskScanKeyStk[TASK_STK_SIZE];
OS_STK TaskDisplayStk[TASK_STK_SIZE];
OS_STK TaskElapsedTimeStk[TASK_STK_SIZE];

// Declare semaphores here

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void TaskStart(void *data); /* Function prototypes of Startup task           */
void TaskScanKey(void *data);
void TaskDisplay(void *data);
void TaskElapsedTime(void *data);
static void TaskStartCreateTasks(void);
static void TaskStartDispInit(void);

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

int main(void)
{
    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK); // Clear the screen

    OSInit(); // Initialize uC/OS-II

    // Create semaphores here

    OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], TaskStartPrio);

    OSStart(); // Start multitasking
    return 0;
}

/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/
void TaskStart(void *pdata)
{

    pdata = pdata; // Prevent compiler warning

    TaskStartDispInit(); // Initialize the display

    TaskStartCreateTasks(); // Create all the application tasks

    //OSStatInit();					// Initialize uC/OS-II's statistics

    for (;;)
    {
        OSTaskSuspend(TaskStartPrio);
    }
}

/*
*********************************************************************************************************
*                                        INITIALIZE THE DISPLAY 
*********************************************************************************************************
*/

static void TaskStartDispInit(void) // Do NOT make any change to TaskStartDispInit()
{
    /*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
    /*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
    //PC_DispStr( 0,  0, "                                                                                ", DISP_FGND_WHITE + DISP_BGND_RED);
    //PC_DispStr( 0,  1, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 0, "                                                                                ", DISP_FGND_WHITE + DISP_BGND_WHITE);
    PC_DispStr(0, 1, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 2, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 3, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 9, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 10, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 11, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 12, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 13, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 14, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 15, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 16, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 17, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 18, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 19, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 20, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 21, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 22, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr(0, 23, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    /*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
    /*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
    PC_DispStr(70, 0, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 1, " CATCH    ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 2, " THE      ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 3, " NUMBERS! ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 4, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 5, " SCORE:   ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 6, " 00000000 ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 7, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 8, " TIME:    ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 9, " 00:00:00 ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 10, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 11, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 12, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 13, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 14, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 15, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 16, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 17, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 18, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 19, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 20, " PRESS    ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 21, " 'ESC'    ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 22, " TO QUIT  ", DISP_FGND_WHITE + DISP_BGND_RED);
    PC_DispStr(70, 23, "          ", DISP_FGND_WHITE + DISP_BGND_RED);
}

/*
*********************************************************************************************************
*                                             CREATE TASKS
*********************************************************************************************************
*/

static void TaskStartCreateTasks(void)
{
    //INT8U  i;

    OSTaskCreate(TaskScanKey, (void *)0, &TaskScanKeyStk[TASK_STK_SIZE - 1], TaskScanKeyPrio);
    OSTaskCreate(TaskDisplay, (void *)0, &TaskDisplayStk[TASK_STK_SIZE - 1], TaskDisplayPrio);
    OSTaskCreate(TaskElapsedTime, (void *)0, &TaskElapsedTimeStk[TASK_STK_SIZE - 1], TaskElapsedPrio);
}

/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/

void TaskDisplay(void *pdata)
{
    //INT8U err;
    char s[15]; // larger string for hh:mm:ss

    for (;;)
    {
        OSTimeDlyHMSM(0, 0, 1, 0);
        //sprintf(s, "%02d:%02d:%02d", elapsed_time_hh, elapsed_time_mm, elapsed_time_ss);
        //PC_DispStr( 71,  9, s, DISP_FGND_WHITE + DISP_BGND_RED);
        //sprintf(s, "%8u", total_score);
        //PC_DispStr(71, 6, s, DISP_FGND_WHITE + DISP_BGND_RED);
    }
}

void TaskScanKey(void *pdata)
{
    INT16S key;

    for (;;)
    {
        if (PC_GetKey(&key) == TRUE)
        { // See if key has been pressed
            switch (key)
            {
            case (0x1B): // See if it's the ESCAPE key
                exit(0); // End program
            case ('D'):  // See if it's the D key.
            case ('d'):
                break;
            }
        }
        OSTimeDly(1);
    }
}

void TaskElapsedTime(void *pdata)
{
    for (;;)
    {
        log_info("%4u: ***** TaskElapsedTime *****\n", OSTime);
        OSTimeDly(1);
    }
}
