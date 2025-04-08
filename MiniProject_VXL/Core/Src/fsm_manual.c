#include "fsm_manual.h"

void run_manual(){
	switch (status1){
	case RED_GREEN_MAN:{
		RedLight1();
		GreenLight2();
		if(count1==0 || isButtonLongPressed(up_button)==1){
			count1 = time_red;
			count2 = time_green;
			status1 = RED_LED_AUTO;
			status2 = GREEN_LED_AUTO;
		}
		if(isButtonPressed(up_button)==1 || uart_press ){
			uart_press=0;
			status1= RED_YELLOW_MAN;
			count1 = timeout*scale;
			count2 = 1;
		}
		break;
	}
	case RED_YELLOW_MAN:{
		RedLight1();
		YellowLight2();
		if(count1==0 || isButtonLongPressed(up_button)==1){
			count1 = time_red - time_green;
			count2 = time_yellow;
			status1 = RED_LED_AUTO;
			status2 = YELLOW_LED_AUTO;
		}
		if(isButtonPressed(up_button)==1 || uart_press ){
			uart_press=0;
			status1= GREEN_RED_MAN;
			count1 = timeout*scale;
			count2 = 1;
		}
		break;
	}
	case GREEN_RED_MAN:{
		GreenLight1();
		RedLight2();
		if(count1==0 || isButtonLongPressed(up_button)==1){
			count1 = time_green;
			count2 = time_red;
			status1 = GREEN_LED_AUTO;
			status2 = RED_LED_AUTO;
		}
		if(isButtonPressed(up_button)==1 || uart_press){
			uart_press=0;
			status1= YELLOW_RED_MAN;
			count1 = timeout*scale;
			count2 = 1;
		}
		break;
	}
	case YELLOW_RED_MAN:{
			YellowLight1();
			RedLight2();
			if(count1==0 || isButtonLongPressed(up_button)==1){
				count1 = time_yellow;
				count2 = time_red - time_green ;
				status1 = YELLOW_LED_AUTO;
				status2 = RED_LED_AUTO;
			}
			if(isButtonPressed(up_button)==1 || uart_press){
				uart_press =0;
				status1= RED_GREEN_MAN;
				count1 = timeout*scale;
				count2 = 1;
			}
			break;

	}
	default:
		break;
	}
	if((status1/10)==2 && count1>0)count1--;
	if((status1/10)==2 && count3>0 ){
				count3--;
				if(count3 ==0){
					count3 = scale;
					/// UART HERE
	//		        char str[40];
	//		        sprintf(str, "Count1: %d - Count2: %d\n\r", count1/10,count2/10);
	//		        HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 100);

			        //LCD L1
			        lcd_clear_display();
			        lcd_goto_XY (1, 0);
			        char str1[20];
			        sprintf(str1, " MANNUAL MODE");
			        lcd_send_string (str1);
			        //LCD L2
			        lcd_goto_XY (0, 0);
			        char str2[20];
			        sprintf(str2, "TIME LEFT: %d", count1/10);
			        lcd_send_string (str2);
				}
	}

}
