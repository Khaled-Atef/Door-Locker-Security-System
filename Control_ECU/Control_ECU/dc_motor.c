/*
 * dc_motor.c
 *
 *  Created on: Jun 18, 2022
 *      Author: khaled Atef
 */

#include <avr/io.h>
#include "common_macros.h"
#include "dc_motor.h"
#include "gpio.h"
#include "std_types.h"
#include "PWM.h"



void motor_Init(void){

	GPIO_setupPinDirection(MOTOR_PORT_ID , MOTOR_IN1_PIN_ID , PIN_OUTPUT) ;
	GPIO_setupPinDirection(MOTOR_PORT_ID , MOTOR_IN2_PIN_ID , PIN_OUTPUT) ;


	/* Motor is stop at the beginning */
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
}


/*
 * Description: Function to rotate the Motor clock wise.
 */
void motor_rotate(motorDirection dir){

	if(dir == CW){

	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_HIGH);



	}else if(dir == ACW){
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);



	}
}


/*
 * Description: Function to rotate the Motor anti clock wise.
 */




/*
 * Description: Function to stop the Motor.
 */

void motor_DeInit(void){
	/* Motor is switched off */

	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);



}
