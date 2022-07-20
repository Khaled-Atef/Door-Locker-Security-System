/*
 * HMI_ECU.h
 *
 *  Created on: Jun 25, 2022
 *      Author: khaled Atef
 */

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

#include "std_types.h"
#include "uart.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TIMER_0_NORMAL_MODE

#ifdef TIMER_0_NORMAL_MODE
#define NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS       458
#define NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE            1830
#elif TIMER_0_COMPARE_MODE
#define NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS       500
#define NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE            2000
#endif

#define MAX_NUMBER_OF_PASSWORD_CHARACTERS      6
#define MAX_NUMBER_OF_ERRORS                   3
#define  DONE                                 0x22
#define  ARE_YOU_READY                        0x1C
#define  NOT_MATCH                            0xCA
#define  NO_ERROR                             0x11
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
 * Description : Function that validate the new password value
 */

void validateTheNewPassWord (void) ;
/*
 * Description : Function used to change the password value
 */
void changePassWord (void) ;
/*
 * Description : Function checks the entered password
 */
void checkPassWord (void) ;
/*
 * Description : function used to enter / re-enter password value
 */
void writePw (void) ;

/*
 * Description : Function used to open the door .
 */
void openDoor (void) ;
/*
 * Description : Function which is responsible for displaying
 *               the main options
 */
void mainOptions (void) ;
/*
 * Description :Function for openning and closing door .
 */
void OpenThenClose (void) ;

// array of function pointer to select the suitable function
void (*selFunc[7])(void) = {mainOptions,openDoor,writePw,checkPassWord,changePassWord,validateTheNewPassWord,OpenThenClose} ;

#endif /* HMI_ECU_H_ */
