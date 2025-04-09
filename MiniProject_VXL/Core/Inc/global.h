#include "stdio.h"
#include "string.h"
#include "main.h"
#include "button.h"
#include "fsm_setting.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "i2c-lcd.h"
#include "scheduler.h"
#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define LED_PINK GPIO_PIN_5 //PA5

#define A1 GPIO_PIN_5 //PB5 red1
#define B1 GPIO_PIN_3 //PB3 green1
#define A2 GPIO_PIN_10 //PB10red2
#define B2 GPIO_PIN_4	//PB4green2
//#define Y1 GPIO_PIN_1
//#define Y2 GPIO_PIN_2
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

//gpioA
#define TX GPIO_PIN_2
#define RX GPIO_PIN_3
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
