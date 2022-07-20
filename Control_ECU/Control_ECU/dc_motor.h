/*
 * dc_motor.h
 *
 *  Created on: Jun 18, 2022
 *      Author: khaled Atef
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "gpio.h"
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MOTOR_PORT_ID                PORTD_ID
#define MOTOR_IN1_PIN_ID             PIN2_ID
#define MOTOR_IN2_PIN_ID		     PIN3_ID

typedef enum{CW,ACW}motorDirection;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


void motor_Init(void) ;

/*
 * Description: Function to rotate the Motor clock wise.
 */
void motor_rotate(motorDirection dir) ;


/*
 * Description: Function to rotate the Motor anti clock wise.
 */



/*
 * Description: Function to stop the Motor.
 */
void motor_DeInit(void) ;



#endif /* DC_MOTOR_H_ */
