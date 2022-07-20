/*
 * timer.h
 *
 *  Created on: Jun 20, 2022
 *      Author: khale
 */

#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TIMER_0_NORMAL_MODE





/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/



/*
 * Description: Function to stop the Timer.
 */
void Timer0_DeInit () ;

/*
 * Description: Function to initiate Timer0
 */
void Timer0_Init_Normal_Mode(void) ;


/*
 * Description: Function to set the Call Back function address.
 */

void Timer_setCallBack(void(*a_ptr)(void)) ;


#endif /* TIMER_H_ */
