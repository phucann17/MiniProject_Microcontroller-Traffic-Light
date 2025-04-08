#include "scheduler.h"



// THE ARRAY OF TASK
static sTask SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task;
//static uint8_t array_Of_Task_ID[SCH_MAX_TASKS];
//static uint32_t newTaskID = 0;
//static uint32_t rearQueue = 0;
//static uint32_t count_SCH_Update = 0;

//static uint32_t Get_New_Task_ID(void);
//static void TIMER_Init(void);

// ERROR CODE
uint8_t Error_code_G ;
uint8_t Error_port ;
uint8_t Last_error_code_G;
uint32_t Error_tick_count_G;

void SCH_Init(){
	uint8_t i;
	for (i = 0; i <SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}
	 // Reset the global error variable
	 // − SCH_Delete_Task() will generate an error code,
	 // (because the task array is empty)
	 Error_code_G= 0;
	 //Timer_init();
	 //MX_IWDG_Init(); //Watchdog init
}

void SCH_Update(void){
	uint32_t Index;
	  //NOTE: calculations are in *TICKS* (not milliseconds)
	for (Index = 0; Index <SCH_MAX_TASKS; Index++) {
	  // Check if there is a task at this location
		if (SCH_tasks_G[Index].pTask){
			if (SCH_tasks_G[Index].Delay == 0) {
				  // The task is due to run
				  // Inc. the ’RunMe’ flag
				SCH_tasks_G[Index].RunMe+= 1;
				if (SCH_tasks_G[Index].Period) {
					  // Schedule periodic tasks to run again
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			} else {
				  // Not yet ready to run: just decrement the delay
				SCH_tasks_G[Index].Delay --;
			}
		}
	}
	//Watchdog_Refresh();
}

uint32_t SCH_Add_Task(void(* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	uint32_t Index = 0;
	// First find a gap in the array (if there is one)
 while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
 	 {
	 	 Index++;
 	 }
 // Havewe reached the end of the list?
 if (Index ==SCH_MAX_TASKS){
 // Task list is full
 // Set the global error variable
 Error_code_G=ERROR_SCH_TOO_MANY_TASKS;
  // Also return an error code
 return SCH_MAX_TASKS;
 }
 // If we’re here, there is a space in the task array
 SCH_tasks_G[Index].pTask = pFunction;
 SCH_tasks_G[Index].Delay = DELAY / TICK;
 SCH_tasks_G[Index].Period = PERIOD / TICK;
 SCH_tasks_G[Index].RunMe = 0;
 SCH_tasks_G[Index].TaskID = Index;
 // return position of task (to allow later deletion)
 return Index;
}

uint8_t SCH_Delete_Task(uint32_t TASK_INDEX){
	uint8_t Return_code;
	if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
	 // No task at this location ...
	 // Set the global error variable
	 Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
	 // ... also return an error code
	 Return_code = RETURN_ERROR;
	 } else {
	 Return_code = RETURN_NORMAL;
	 }
	 SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	 SCH_tasks_G[TASK_INDEX]. Delay = 0;
	 SCH_tasks_G[TASK_INDEX]. Period = 0;
	 SCH_tasks_G[TASK_INDEX].RunMe = 0;
	 return Return_code; // return status
}

void SCH_Dispatch_Task(void){
	// Dispatches (runs) the next task (if one is ready)
	uint8_t Index;
	 // Dispatches (runs) the next task (if one is ready)
	for (Index = 0; Index <SCH_MAX_TASKS; Index++){
		if (SCH_tasks_G[Index].RunMe> 0) {
			(*SCH_tasks_G[Index].pTask)(); // Run the task
			SCH_tasks_G[Index].RunMe--; // Reset / reduceRunMe flag
			// Periodic tasks will automatically run again
			// − if this is a ’one shot’ task, remove it from the array
			if (SCH_tasks_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
		}
	}
	// Report system status
	SCH_Report_Status();
	// The scheduler enters idlemode at this point
	//SCH_Go_To_Sleep();
}

void SCH_Go_To_Sleep(){}

void SCH_Report_Status(void) {
#ifdef SCH_REPORT_ERRORS
	//ONLYAPPLIES IFWEAREREPORTINGERRORS
	// Check for answer error code
	if (Error_code_G != Last_error_code_G) {
		// Negative logic onLEDs assumed
		Error_port = 255 - Error_code_G;
		Last_error_code_G = Error_code_G;
		if (Error_code_G != 0){
			Error_tick_count_G= 60000;
		} else {
			Error_tick_count_G= 0;
		}
	}
	else {
		if (Error_tick_count_G != 0){
			if (--Error_tick_count_G== 0) {
				Error_code_G= 0; // Reset error code
			}
		}
	}
#endif
}


/*

 voidHAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
 SCH_Update() ;
 }

*/

/*

The dispatcher is the only component in the SuperLoop:
void main(void){
while(1){
	SCH_Dispatch_Tasks() ;
}

*/

////INIT TIMER_10ms
//static void TIMER_Init()
//    cli(); //Disable interupt
//
//    /*Reset Timer/counter1*/
//    TCCR1A = 0;
//    TCCC1B = 0;
//    TIMSK = 0;
//
//    /*Set up timer/counter 1*/
//    TCC1B != (1 << CS11)| (1 << CS10); //Prescale = 64
//    TCNT1 = CONTER_START;
//    TIMSK1 = (1<<TOIE1); // Overflow interupt enable
//    sei(); //Enable interupt
//}
//
//ISR (TIMER_OVF_vect){
//    TCNT1 = CONTER_START;
//    SCH_Update();
//}
//
//static uint32_t Get_New_Task_ID(void){
//    newTaskID++;
//    if(newTaskID == NO_TASK_ID){
//        newTaskID++;
//    }
//    return newTaskID;
//}


//WATCHDOG
//IWDG_HandleTypeDef hiwdg;
//static uint32_t counter_for_watchdog = 0;
//
//void MX_IWDG_Init(void) {
//    hiwdg.Instance = IWDG;
//    hiwdg.Init.Prescaler = IWDG_PRESCALER_32; // Chia tần số để định thời gian cho watchdog
//    hiwdg.Init.Reload = 4095; // Giá trị reload để định thời gian
//    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
//        Error_Handler(); // Gọi hàm xử lý lỗi nếu khởi tạo thất bại
//    }
//}
//
//
//
//void Watchdog_Refresh(void) {
//    HAL_IWDG_Refresh(&hiwdg); // Làm mới watchdog
//}
//
//
//uint8_t Is_Watchdog_Reset(void){
//  if(counter_for_watchdog > 3){
//	  return 1;
//  }
//  	  return 0;
//}
//
//void Watchdog_Counting(void){
//  counter_for_watchdog++;
//}
//
//void Reset_Watchdog_Counting(void){
//  counter_for_watchdog = 0;
//}

