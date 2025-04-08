#include "button.h"
const int MAX_BUTTON = 2;
int button_flag[2] = {0, 0};

int KeyReg0[2] = {NORMAL_STATE, NORMAL_STATE};
int KeyReg1[2] = {NORMAL_STATE, NORMAL_STATE};
int KeyReg2[2] = {NORMAL_STATE, NORMAL_STATE};
int KeyReg3[2] = {NORMAL_STATE, NORMAL_STATE};

int button_long_flag[2] = {0, 0};
int TIME[2] = {200, 200};
int time = 200;


int isButtonPressed(int idx){
	if (button_flag[idx] == 1){
		button_flag[idx] = 0;
		return 1;
	}
	return 0;
}
int isButtonLongPressed(int idx){
	if (button_long_flag[idx] == 1){
		button_long_flag[idx] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
	for (int i = 0; i < MAX_BUTTON; i++){
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[0] = HAL_GPIO_ReadPin(GPIOA, UP_BUTTON);
		KeyReg2[1] = HAL_GPIO_ReadPin(GPIOA, SET_BUTTON);

		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg3[i] != KeyReg2[i]){
				KeyReg3[i] = KeyReg2[i];

				if (KeyReg3[i] == PRESSED_STATE){
					TIME[i] = 200;
					button_flag[i] = 1;
				}
			}else{
				if (KeyReg3[i] == PRESSED_STATE){
					if (TIME[i] > 0){
						TIME[i]--;
					}
					else{
						button_long_flag[i] = 1;
						TIME[i] = 200;
						//KeyReg3[i] = NORMAL_STATE;
					}
				}
//				TIME[i]--;
//				if (TIME[i] == 0){
//					KeyReg3[i] = NORMAL_STATE;
//				}
			}
		}
	}
}
