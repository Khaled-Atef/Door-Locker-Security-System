/*
 * buzzer.h
 *
 *  Created on: Jun 18, 2022
 *      Author: khaled Atef
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"

#define BUZZER_PORT_ID         PORTC_ID
#define BUZZER_PIN_ID          PIN5_ID

/*
 * Description: Function to initiate the Alarm .
 */

void Alarm_Init (void) ;

/*
 * Description: Function to Start the Alarm .
 */

void Alarm_On (void) ;

/*
 * Description: Function to shut off the Alarm .
 */

void Alarm_Off (void) ;


#endif /* BUZZER_H_ */
