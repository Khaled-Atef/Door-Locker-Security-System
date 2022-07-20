/*
 * Control_ECU.h
 *
 *  Created on: Jun 26, 2022
 *      Author: khaled Atef
 */

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MAX_NUMBER_OF_PASSWORD_CHARACTERS      6
#define  WRONG_PASSWORD                       0xAC
#define  CORRECT_PASSWORD                     0x00
#define  NOT_MATCH                            0xCA
#define  NO_ERROR                             0x11
#define  ARE_YOU_READY                        0x1C
#define  DONE                                 0x22
#define  NEXT                                 0x55
#define  VALIDATION                           0x3F
#define  CHANGE_PASSWORD                      0xA1
#define  SAVE_PASSWORD                        0x19
#define  NEW                                  0x5A
#define  MOTOR_CONFIGURATION                  0x09
#define  THIEVES                              0xE3


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: Function to configure the motor rotation direction
 */
void motorSetup (void) ;
/*
 * Description: Function that verify the new password
 */
void verifyNewPassWord (void) ;
/*
 * Description: Function creates the new password
 */
void createNewPassWord (void) ;
/*
 * Description: This Function validate both the entered password value
 * to open the door .
 */
void testPassWordValue (void) ;
/*
 * Description: Function to start the alarm and stop it if the password
 * is not matching for more than three times
 */
void Alarm (void) ;
/*
 * Description: Function for calculating the duration for both rotating the motor
 * or starting the alarm
 */
void secondProcessing(void) ;




#endif /* CONTROL_ECU_H_ */
