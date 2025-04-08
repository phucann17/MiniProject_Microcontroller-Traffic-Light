/*
 * fsm_automatic.c
 *
 *  Created on: Apr 5, 2025
 *      Author: Admin
 */
#include "fsm_automatic.h"
void run_automatic(){
	switch (status1){
		case INIT:
			ResetLight1();
			status1 = RED_LED_AUTO;
			count1 = time_red;
			lcd_clear_display();
			break;

		case RED_LED_AUTO:
			RedLight1();
			if (count1 == 0){
				status1 = GREEN_LED_AUTO;
				count1 = time_green;
			}
			if (isButtonLongPressed(up_button)){
				ResetLight1();
				ResetLight2();
				status1 = RED_GREEN_MAN;
				status2 = RED_GREEN_MAN;
				count1 = scale*10;
				count2 = 1;
			}
			break;

		case GREEN_LED_AUTO:
			GreenLight1();
			if (count1 == 0){
				status1 = YELLOW_LED_AUTO;
				count1 = time_yellow;
			}
			break;

		case YELLOW_LED_AUTO:
			YellowLight1();
			if (count1 == 0){
				status1 = RED_LED_AUTO;
				count1 = time_red;
			}
			break;

		default:
			break;
	}

	switch (status2){
			case INIT:
				ResetLight2();
				status2 = GREEN_LED_AUTO;
				count2 = time_green;
				lcd_clear_display();
				break;

			case RED_LED_AUTO:
				RedLight2();
				if (count2 == 0){
					status2 = GREEN_LED_AUTO;
					count2 = time_green;
				}
				break;

			case GREEN_LED_AUTO:
				GreenLight2();
				if (count2 == 0){
					status2 = YELLOW_LED_AUTO;
					count2 = time_yellow;
				}
				break;

			case YELLOW_LED_AUTO:
				YellowLight2();
				if (count2 == 0){
					status2 = RED_LED_AUTO;
					count2 = time_red;
				}
				break;
			default:
				break;
		}
	if ((status1/10) == 1 && count1 > 0) count1--;
	if ((status2/10) == 1 && count2 > 0) count2--;
}
