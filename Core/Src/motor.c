/**
  ******************************************************************************
  * @file    shell.c
  * @brief   This file provides code for motor control
  ******************************************************************************
  *  Created on: Nov 7, 2022
  *      Author: nicolas
  *
  ******************************************************************************
  */

#include "motor.h"

/**
  * @brief  Switch on the motor driver
  * @note Activates the chopper's reset signal, situated on its 33rd pin
  * @retval None
  */
void motorPowerOn(void){
	HAL_GPIO_WritePin(ISO_RESET_GPIO_Port, ISO_RESET_Pin, GPIO_PIN_SET);
	int i;
	for (i=0;i<30; i++)
	{
	}
	HAL_GPIO_WritePin(ISO_RESET_GPIO_Port, ISO_RESET_Pin, GPIO_PIN_RESET);
}

/**
  * @brief  Switch off the motor driver
  * @retval None
  */
void motorPowerOff(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // just for test, you can delete it
}
/**
 * @brief Set the PWM duty cycle
 * @param alpha
 */
void setdutycycle(int alpha)
{
		if (alpha < 0 || alpha > 100){
			        return;
		}
	TIM1->CCR1=(alpha*5312)/100;
	TIM1->CCR2=5311-(alpha*5312)/100;
}

/**
  * @brief  Set the motor speed
  * @param  speed : target speed of the motor
  * @retval None
  */
void motorSetSpeed(int speed){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // just for test, you can delete it
}
