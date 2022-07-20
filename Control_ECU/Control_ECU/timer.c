/*
 * timer.c
 *
 *  Created on: Jun 18, 2022
 *      Author: khaled Atef
 */

#include "timer.h"
#include "std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPointer)(void) = NULL_PTR;



/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

#ifdef TIMER_0_NORMAL_MODE

ISR(TIMER0_OVF_vect){

	if(g_callBackPointer != NULL_PTR){
		(*g_callBackPointer)() ;

	}

}

#elif TIMER_0_COMPARE_MODE
ISR(TIMER0_COMP_vect){

	if(g_callBackPointer != NULL_PTR){
		(*g_callBackPointer)() ;
	}

}

#endif

/* Description :
 * For clock=8Mhz and prescale F_CPU/1024 every count will take 1ms
 * so put initial timer counter = 0  0 --> 255 (256ms per overflow)
 * so we need timer to overflow 458 times to get a 15 seconds
 */


#ifdef TIMER_0_NORMAL_MODE

void Timer0_Init_Normal_Mode (){
	TCNT0 = 0 ; //Set Timer initial value to 0
	TIMSK |=(1<<TOIE0) ; // Enable Timer0 Overflow Interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<CS00) | (1<<CS02) ;
}

#elif TIMER_0_COMPARE_MODE

void Timer0_Init_CTC_Mode (){
	TCNT0 = 0;    // Set Timer initial value to 0
	OCR0  = 235; // Set Compare Value
	TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS00) | (1<<CS02);
}

#endif

/*
 * Description: Function to stop the Timer.
 */

void Timer0_DeInit (){
	TCCR0 &=(~(1<<CS00)) ;
	TCCR0 &=(~(1<<CS01)) ;
	TCCR0 &=(~(1<<CS02)) ;
}



/*
 * Description: Function to set the Call Back function address.
 */


void Timer_setCallBack(void(*a_ptr)(void)){
	g_callBackPointer = a_ptr ;
}
