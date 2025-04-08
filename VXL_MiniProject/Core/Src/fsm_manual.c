/*
 * fsm_manual.c
 *
 *  Created on: Apr 5, 2025
 *      Author: Admin
 */
#include "fsm_manual.h"
void run_manual(){
	switch (status1){
		case RED_GREEN_MAN:
			RedLight1();
			GreenLight2();
			if (isButtonLongPressed(up_button) == 1 || count1 == 0){
				count1 = time_red;
				count2 = time_green;
				status1 = RED_LED_AUTO;
				status2 = GREEN_LED_AUTO;
			}
			if (isButtonPressed(up_button) == 1){
				status1 = RED_YELLOW_MAN;
				count1 = timeout * scale;
				count2 = 1;
			}
			break;
		case RED_YELLOW_MAN:
			RedLight1();
			YellowLight2();
			if (isButtonLongPressed(up_button) == 1 || count1 == 0){
				count1 = time_red - time_green;
				count2 = time_yellow;
				status1 = RED_LED_AUTO;
				status2 = YELLOW_LED_AUTO;
			}
			if (isButtonPressed(up_button) == 1){
				status1 = GREEN_RED_MAN;
				count1 = timeout * scale;
				count2 = 1;
			}
			break;
		case GREEN_RED_MAN:
			GreenLight1();
			RedLight2();
			if (isButtonLongPressed(up_button) == 1 || count1 == 0){
				count1 = time_green;
				count2 = time_red;
				status1 = GREEN_LED_AUTO;
				status2 = RED_LED_AUTO;
			}
			if (isButtonPressed(up_button) == 1){
				status1 = YELLOW_RED_MAN;
				count1 = timeout * scale;
				count2 = 1;
			}
			break;
		case YELLOW_RED_MAN:
			YellowLight1();
			RedLight2();
			if (isButtonLongPressed(up_button) == 1 || count1 == 0){
				count1 = time_yellow;
				count2 = time_red - time_green;
				status1 = YELLOW_LED_AUTO;
				status2 = RED_LED_AUTO;
			}
			if (isButtonPressed(up_button) == 1){
				status1 = RED_GREEN_MAN;
				count1 = timeout * scale;
				count2 = 1;
			}

			break;
		default:
			break;
	}
	if ((status1/10 == 2) && count1 > 0) count1--;
}

