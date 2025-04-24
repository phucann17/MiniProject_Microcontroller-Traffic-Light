#include "global.h"
int time_red = 5 * scale ;
int time_yellow = 2 * scale  ; // red = green + yellow
int time_green = 3 * scale ;

int status1 =INIT;
int status2 =INIT;
int count1 =0; //COUNTDOWN TRAFFIC LIGHT 1
int count2 =0; //COUNTDOWN TRAFFIC LIGHT 2
int count3 =scale; //COUNTDOWN TOGGLE LED
int uart_mode1=0;
int uart_press=0;
int timeout=2;
void GPIO_Init(void){
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
	                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10
	                          |GPIO_PIN_11, GPIO_PIN_RESET);

	  /*Configure GPIO pins : PA1 PA2 PA3 PA4
	                           PA5 PA6 PA7 */
	  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
	                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pins : PA8 PA9 */
	  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pins : PA10 PA11 */
	  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

void ResetLight1(){
	HAL_GPIO_WritePin(GPIOB,A1, RESET);
	HAL_GPIO_WritePin(GPIOB,B1 , RESET);
	// HAL_GPIO_WritePin(GPIOB,Y1 , RESET);
}

void RedLight1(){
	HAL_GPIO_WritePin(GPIOB,A1, SET);
	HAL_GPIO_WritePin(GPIOB,B1, SET);
	// HAL_GPIO_WritePin(GPIOB,Y1 , RESET);
}

void YellowLight1(){
	HAL_GPIO_WritePin(GPIOB,A1, SET);
	HAL_GPIO_WritePin(GPIOB,B1 , RESET);
	// HAL_GPIO_WritePin(GPIOB,Y1 , SET);
}

void GreenLight1(){
	HAL_GPIO_WritePin(GPIOB,A1, RESET);
	HAL_GPIO_WritePin(GPIOB,B1, SET);
	// HAL_GPIO_WritePin(GPIOB,Y1 , RESET);
}

void RedLight2(){
	HAL_GPIO_WritePin(GPIOB,A2, SET);
	HAL_GPIO_WritePin(GPIOB,B2 , SET);
	// HAL_GPIO_WritePin(GPIOB,Y2 , RESET);
}

void YellowLight2(){
	HAL_GPIO_WritePin(GPIOB,A2, SET);
	HAL_GPIO_WritePin(GPIOB,B2 , RESET);
	// HAL_GPIO_WritePin(GPIOB,Y2 , SET);
}
void GreenLight2(){
	HAL_GPIO_WritePin(GPIOB,A2, RESET);
	HAL_GPIO_WritePin(GPIOB,B2 , SET);
	// HAL_GPIO_WritePin(GPIOB,Y1 , RESET);
}

void ResetLight2(){
	HAL_GPIO_WritePin(GPIOB,A2, RESET);
	HAL_GPIO_WritePin(GPIOB,B2 , RESET);
	// HAL_GPIO_WritePin(GPIOB,Y2 , RESET);
}

void BlinkLed(){
	HAL_GPIO_TogglePin(GPIOA, LED_PINK);
}

void Run_Traffic_Light(){
	run_setting();
	run_manual();
	run_automatic();
}

