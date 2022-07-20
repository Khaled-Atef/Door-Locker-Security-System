/*
 * HMI_ECU.c
 *
 *  Created on: Jun 20, 2022
 *      Author: khaled Atef
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "timer.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "HMI_ECU.h"
#include "std_types.h"

uint8 key ;
uint8 change ;
uint8 error = 0 ;
uint8 enter = 0 ;
uint8 g_flag = 0 ;
uint8 g_select = 0 ;
uint8 g_configure = 0 ;
uint16 g_cycleCount = 0 ;
/*
 * Description : Function displays the message "Door is openned" for
 * 15 seconds then receives DONE from Control_ECU to call itself again
 * but with displaying the message "Door is closed" for 15 seconds
 * then it call itself again with displaying the main menu
 */

void OpenThenClose (void){

	if(g_configure == 0){
		g_configure = 1 ;
		LCD_displayString("Door is OPenned ");
#ifdef TIMER_0_NORMAL_MODE
		Timer0_Init_Normal_Mode() ;
#elif TIMER_0_COMPARE_MODE
		Timer0_Init_CTC_Mode();
#endif
		while(UART_recieveByte() != DONE ){} ;
		g_select = 6 ;

	}else if(g_configure == 1){
		g_configure = 2 ;
		LCD_displayString("Door is Closed ");
#ifdef TIMER_0_NORMAL_MODE
		Timer0_Init_Normal_Mode() ;
#elif TIMER_0_COMPARE_MODE
		Timer0_Init_CTC_Mode();
#endif
		while(UART_recieveByte() != DONE ){} ;
		g_select = 6 ;

	}else if(g_configure == 2){
		g_select = 0 ;
	}


	return ;

}


void secondProcessing(void){
	g_cycleCount ++ ;
	if(g_cycleCount == NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS){
		g_cycleCount = 0 ;
		Timer0_DeInit() ;
		LCD_clearScreen() ;
	}
}

/*
 * Description : Function that validate the new password value
 * if the second entry of the new password value matches the first
 * entry of the new password value the password is saved otherwise
 * it will require to repeat the steps again of changing password
 */

void validateTheNewPassWord (){

	if(UART_recieveByte() == NOT_MATCH){
		LCD_clearScreen() ;
		LCD_displayString("---ERROR!!---");
		_delay_ms(3000) ;
		LCD_clearScreen() ;
		LCD_displayString("REPEAT STEPS AGAIN");
		g_select = 4 ;// call changePassWord() Function

	}else{
		LCD_clearScreen() ;
		_delay_ms(15000) ;
		LCD_displayString("PASS WORD SAVED!");
		_delay_ms(15000) ;
		LCD_clearScreen() ;
		g_select = 0 ;// call mainOptions() Function
	}
	g_flag = 0 ;
	enter = 0 ;

	return ;

}


/*
 * Description: Function used to change the password value
 * it will require to enter the new value of the password
 * then it will require to enter this value again
 */

void changePassWord (void){
	if(enter == 0 ){
	    g_flag = 1 ;
		enter ++ ;
		LCD_clearScreen() ;
		LCD_displayString("please enter new password : ") ;
		LCD_moveCursor(1,0) ;
		g_select = 2 ;// call writePw() Function
		return ;
	}else if(enter == 1 ){
	    g_flag = 2 ;
		enter ++ ;
		LCD_clearScreen() ;
		LCD_displayString("please Re-enter new password : ");
		LCD_moveCursor(1,0) ;
		g_select = 2 ;// call writePw() Function
		return ;

	}

	return ;

}

/*
 * Description : Function checks the entered password if it is true
 * it is OK it will return back to re-enter the password value if it is
 * true the door is openned .
 * other wise it returns error if the the user entered the password
 * wrong for more than three times it will display "THIEVES"
 *
 */

void checkPassWord (){
	if(UART_recieveByte() == NOT_MATCH){
		error ++ ;
		enter = 0 ;
		LCD_clearScreen() ;
		LCD_displayString("---ERROR!!---");
		_delay_ms(3000) ;
		if(error == MAX_NUMBER_OF_ERRORS){
			error = 0 ;
			LCD_clearScreen() ;
			LCD_displayString("THEIVES!!! ");
			_delay_ms(3000) ;
			UART_sendByte(THIEVES) ;
			while(UART_recieveByte() != DONE){} ;
			LCD_clearScreen() ;
			g_select = 0 ;
			return ;
		}
		g_select = 1 ;// call openDoor() Function
		return ;

	}else{

		error = 0 ;
		g_select = 1 ;// call openDoor() Function
		return ;

	}
}

/*
 * Description : function used to enter password value , re-enter password value
 * also for enter the value of the new password and re-enter the new password
 */


void writePw (){
	uint8 count = 0 ;
	while (count < MAX_NUMBER_OF_PASSWORD_CHARACTERS){
		UART_sendByte(ARE_YOU_READY) ;
		_delay_ms(3000);
		/* if any switch pressed for more than 3000 ms it counts more than one press */
		key = KEYPAD_getPressedKey() ;// store the pressed value of the keypad in a variable
		while(UART_recieveByte() != DONE ){} ; // wait until it receives DONE from the Control_ECU
		UART_sendByte(key) ; // send the pressed value of the keypad to Control_ECU
		LCD_displayCharacter('*');
		_delay_ms(3000);
		count++ ;
		while(UART_recieveByte() != NEXT ){} // wait until it receives the request of the new value
	}
	if(g_flag == 0){
    	g_select = 3 ; // it will call checkPassWord () Function
	}else if(g_flag == 1){
		g_select = 4 ;// it will call changePassWord() Function
	}else{
		g_select = 5 ; // it will call validateTheNewPassWord() Function
	}
	return ;

}

/*
 * Description : Function used to open the door
 */


void openDoor (){
	if(enter == 0){
		enter ++ ;
		LCD_clearScreen() ;
		LCD_displayString("please enter your password : ");
		LCD_moveCursor(1,0) ;
		g_select = 2 ; // it will call writePw() Function
		return ;

	}else if(enter == 1){
		enter ++ ;
		LCD_clearScreen() ;
		UART_sendByte(VALIDATION) ;
		LCD_displayString("please Re-enter your password : ");
		LCD_moveCursor(1,0) ;
		g_select = 2 ; // it will call writePw() Function

	}else{
		enter = 0 ;
		LCD_clearScreen() ;
		g_select = 6 ; // it will call OpenThenClose() Function
		return ;
	}
	return ;

}

/*
 * Description : Function which is responsible for displaying
 *               the main options
 *               to open the door the user have to press the '+' button
 *               to change the password the user have to press the '-' button
 */
void mainOptions (){

	LCD_displayString("+ : Open Door") ;
	LCD_moveCursor(1,0) ;
	LCD_displayString("- : Change PassWord") ;
	key = KEYPAD_getPressedKey() ;

	if(key == '+'){
		LCD_clearScreen() ;
		g_select = 1 ;

	}else{
		LCD_clearScreen() ;
		g_select = 4 ;
	}

	return ;
}



int main (void){
	uint8 x ;
	LCD_init() ;
	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(9600) ;
	SREG |=(1<<7) ;//Enable global interrupts in MC by setting the I-Bit.
	/* Set the Call back function pointer in the TIMER driver */
	Timer_setCallBack(secondProcessing) ;


	while(1){
		x = g_select ;

		switch(x){

		case 0:
			// call mainOptions() Function
			(*selFunc[g_select])() ;
			break ;

		case 1:
			UART_sendByte(VALIDATION) ;
			// call openDoor() Function
			(*selFunc[g_select])() ;
			break ;

		case 2:
			// call writePw() Function
			(*selFunc[g_select])() ;
			break ;

		case 3:
			// call checkPassWord() Function
			(*selFunc[g_select])() ;
			break ;

		case 4:
			if (g_flag == 0){
				UART_sendByte(CHANGE_PASSWORD) ;
				// call changePassWord() Function
				(*selFunc[g_select])() ;

			}else{

				if (g_flag == 1){
					UART_sendByte(SAVE_PASSWORD) ;
					// call changePassWord() Function
					(*selFunc[g_select])() ;
				}
			}
			break ;

		case 5:
			// call validateTheNewPassWord() Function
			(*selFunc[g_select])() ;
			break ;

		case 6:
			UART_sendByte(MOTOR_CONFIGURATION) ;
			// call OpenThenClose() Function
			(*selFunc[g_select])() ;
			break ;


		}


	}



	}


