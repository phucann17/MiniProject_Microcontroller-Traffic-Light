/*
 * scheduler.h
 *
 *  Created on: Nov 13, 2024
 *      Author: ASUS
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

// INCLUDE
#include "main.h"
#include "stdint.h"


// DEFINE OPTION
#define SCH_REPORT_ERRORS 0

// DEEFINE SCH_ERROR
#define ERROR_SCH_NO_ERROR 0
#define ERROR_SCH_TOO_MANY_TASKS 1
#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK 2;
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER 3;
#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START 4;
#define ERROR_SCH_LOST_SLAVE 5;
#define ERROR_SCH_CAN_BUS_ERROR 6;
#define ERROR_I2C_WRITE_BYTE_AT24C64 7;
#define ERROR_SCH_CANNOT_DELETE_TASK 8;

// DEEFINE RETURN
#define RETURN_ERROR -1;
#define RETURN_NORMAL 0;

// STRUCT TASK
#define TICK 10 //tick = 10ms
#define NO_TASK_ID 0
#define SCH_MAX_TASKS 40

typedef struct{
    void (* pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskID;
} sTask;

// FUNTION
void SCH_Init(void);
void SCH_Update(void); // Like timerrun
uint32_t SCH_Add_Task(void(* pFunction)(), uint32_t DELAY, uint32_t PERIOD); //Like settimer
void SCH_Dispatch_Task(void); //Timerflag
uint8_t SCH_Delete_Task(uint32_t taskID);
void SCH_Report_Status(void);
void SCH_Go_To_Sleep();

//WATCH DOG
void MX_IWDG_Init(void);
void Watchdog_Refresh(void);
uint8_t Is_Watchdog_Reset(void);
void Watchdog_Counting(void);
void Reset_Watchdog_Counting(void);


#endif /* INC_SCHEDULER_H_ */
