/*
 * fsm_setting.c
 *
 *  Created on: Apr 7, 2025
 *      Author: Admin
 */
#include "fsm_setting.h"

int tmp_red=0;
int tmp_yellow=0;
int tmp_green=0;
int flag =1;
int flag1 = 0;

void run_setting(){
	if (status1 / 10 != 3){
		if (isButtonLongPressed(set_button)){
			count3 = 1*scale;
			status1 = RED_LED_SET;
			status2 = RED_LED_SET;
			count1 = 2;
			count2 = time_red;
			ResetLight1();
			ResetLight2();
			flag=1;
		}
	}

	switch (status1){
		case RED_LED_SET:
			if (count3 == 0){
				count3 = 1*scale;
				HAL_GPIO_TogglePin(GPIOB, A1);
				HAL_GPIO_TogglePin(GPIOB, A2);
			}

			if (isButtonPressed(up_button)){
				count2 += scale;
				if (count2 > 99*scale) count2 = scale;
				flag = 1;
			}

			if (isButtonPressed(set_button)){
				tmp_red = count2;
				count3 = 3*scale;
				RedLight1();
				RedLight2();
			}

			if (isButtonLongPressed(set_button)){
				count2 = time_yellow;
				count1 = 3;
				ResetLight1();
				ResetLight2();
				status1 = YELLOW_LED_SET;
				flag = 1;
			}

			break;
		case YELLOW_LED_SET:
				if (count3 == 0){
					count3 = 1*scale;
					HAL_GPIO_TogglePin(GPIOB, Y1);
					HAL_GPIO_TogglePin(GPIOB, Y2);
				}

				if (isButtonPressed(up_button)){
					count2 += scale;
					if (count2 > 99*scale) count2 = scale;
					flag = 1;
				}

				if (isButtonPressed(set_button)){
					tmp_green = count2;
					count3 = 3*scale;
					YellowLight1();
					YellowLight2();
				}

				if (isButtonLongPressed(set_button)){
					count2 = time_yellow;
					count1 = 4;
					ResetLight1();
					ResetLight2();
					status1 = GREEN_LED_SET;

					flag = 1;
				}
			break;
		case GREEN_LED_SET:
				if (count3 == 0){
					count3 = 1*scale;
					HAL_GPIO_TogglePin(GPIOB, B1);
					HAL_GPIO_TogglePin(GPIOB, B2);
				}

				if (isButtonPressed(up_button)){
					count2 += scale;
					if (count2 > 99*scale) count2 = scale;
					flag = 1;
				}

				if (isButtonLongPressed(set_button)){
					if (tmp_red == tmp_yellow + tmp_green){
						time_red = tmp_red;
						time_yellow = tmp_yellow;
						time_green = tmp_green;
					}
					status1 = INIT;
					status2 = INIT;
				}

				if (isButtonPressed(set_button)){
					tmp_green = count2;
					count3 = 3*scale;
					GreenLight1();
					GreenLight2();
				}
			break;

		default:
			break;
	}

	if (status1 / 10 == 3 && count3 > 0) count3--;
}
