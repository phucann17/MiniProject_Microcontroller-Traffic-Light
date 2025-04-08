#include "scheduler.h"
sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t start = 0;
uint8_t end = 0;

void SCH_Init(void){
	int i;
	for (i = 0; i < SCH_MAX_TASKS; i++){
		SCH_tasks_G[i].pTask = 0x0000;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
		SCH_tasks_G[i].isRun = 0;
	}
	start = end = 0;
}

void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if ((end + 1) % SCH_MAX_TASKS == start){
		return;
	}
	for (int i = start; i != end; i = (i + 1) % SCH_MAX_TASKS){
		if (pFunction == SCH_tasks_G[i].pTask){
			return;
		}
	}
	SCH_tasks_G[end].pTask = pFunction;
	SCH_tasks_G[end].Delay = DELAY / TICK;
	SCH_tasks_G[end].Period = PERIOD / TICK;
	SCH_tasks_G[end].isRun = 1;
	SCH_tasks_G[end].RunMe = 0;
	end = (end + 1) % SCH_MAX_TASKS;
}

void SCH_Delete_Task(uint8_t task_index){
	if (start == end) return;

	uint8_t i = task_index;
	while (i != end){
		uint8_t next = (i + 1) % SCH_MAX_TASKS;
		SCH_tasks_G[i] = SCH_tasks_G[next];
		i = next;
	}

	end = (end - 1 + SCH_MAX_TASKS) % SCH_MAX_TASKS;
}

void SCH_Update(void){
	if (start != end && SCH_tasks_G[start].isRun == 1){
		if (SCH_tasks_G[start].Delay > 0){
			SCH_tasks_G[start].Delay--;
		}
		else{
			SCH_tasks_G[start].RunMe = 1;

			if (SCH_tasks_G[start].Period > 0){
				SCH_tasks_G[start].Delay = SCH_tasks_G[start].Period;
				SCH_tasks_G[end] = SCH_tasks_G[start];
				end = (end + 1) % SCH_MAX_TASKS;
			}
			start = (start + 1) % SCH_MAX_TASKS;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	if (SCH_tasks_G[start].RunMe > 0 && start != end && SCH_tasks_G[start].isRun == 1){
		SCH_tasks_G[start].RunMe = 0;

		(*SCH_tasks_G[start].pTask)();

		if (SCH_tasks_G[start].Period == 0) {
		    start = (start + 1) % SCH_MAX_TASKS;
		}

	}
}
