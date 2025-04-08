#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

//INCLUDE LIBRARY
#include "main.h"
#include "button.h"
#include "scheduler.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "fsm_setting.h"
#include "i2c-lcd.h"
#include "string.h"
#include "stdio.h"

//DEFINE GPIO PIN - PORT A
//#define LED_PINK GPIO_PIN_1
//#define LED_RED_1  GPIO_PIN_4
//#define LED_YELLOW_1  GPIO_PIN_5
//#define LED_GREEN_1  GPIO_PIN_6
//#define LED_RED_2  GPIO_PIN_7
//#define LED_YELLOW_2  GPIO_PIN_8
//#define LED_GREEN_2  GPIO_PIN_9

#define LED_PINK GPIO_PIN_5 //PA5

#define A1 GPIO_PIN_5 //PB5
#define B1 GPIO_PIN_3 //PB3
#define A2 GPIO_PIN_10 //PB10
#define B2 GPIO_PIN_4	//PB4

//DEFINE STATE
#define INIT 0

#define RED_LED_AUTO 11
#define YELLOW_LED_AUTO 12
#define GREEN_LED_AUTO 13

#define RED_GREEN_MAN 21
#define	RED_YELLOW_MAN 22
#define GREEN_RED_MAN 23
#define YELLOW_RED_MAN 24

#define RED_LED_SET 31
#define YELLOW_LED_SET 32
#define GREEN_LED_SET 33


//DEFINE BUTTON FLAG

#define up_button 0
#define set_button 1


// SCALE TIME
#define scale 10 // SCALE = 1000/ cycle of traffic_light_run

//DEFINE VARIABLE
extern int status1;
extern int status2;
extern int lockcount1;
extern int lockcount2;
extern int count1;
extern int count2;
extern int count3;

extern int time_red;
extern int time_yellow; // red = green + yellow
extern int time_green;

extern UART_HandleTypeDef huart2;
extern int uart_mode1;
extern int uart_press;
extern int timeout;

//DEFINE FUNTION

void GPIO_Init(void);
void ResetLight1();
void ResetLight2();
void RedLight1();
void YellowLight1();
void GreenLight1();
void RedLight2();
void YellowLight2();
void GreenLight2();
void BlinkLed();
void Run_Traffic_Light();


#endif /* INC_GLOBAL_H_ */
