/*
 * button.h
 *
 *  Created on: Oct 5, 2023
 *      Author: KAI
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"
#define NORMAL_STATE SET
#define PRESSED_STATE RESET

extern const int MAX_BUTTON;
extern int button_flag[2];
//extern int button_flagg;

//DEFINE BUTTON GPIO A
#define UP_BUTTON GPIO_PIN_8
#define SET_BUTTON GPIO_PIN_9

void getKeyInput();
int isButtonPressed(int idx);
int isButtonLongPressed(int idx);

#endif /* INC_BUTTON_H_ */

