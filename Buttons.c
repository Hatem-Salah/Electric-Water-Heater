/*
 * Buttons.c
 *
 * Created: 3/20/2021 7:00:44 PM
 *  Author: Hatem
 */ 

#include "Buttons.h"

/*----------------------------------------------------------------------------*-
Buttons_init() : to initialize Buttons by making their pins as INPUT pins,
enabling the internal pull-up resistor, and enabling the external interrupt
for the ON/OFF button.
-*----------------------------------------------------------------------------*/

void Buttons_init(void){
	// Setting the pins as INPUT pins
	clr_bit(B_PORT_DIR,ON_OFF_PIN);
	clr_bit(B_PORT_DIR,UP_PIN);
	clr_bit(B_PORT_DIR,DOWN_PIN);	
	
	// Enable internal Pull-Up Resistor
	
	set_bit(B_PORT,ON_OFF_PIN);
	set_bit(B_PORT,UP_PIN);
	set_bit(B_PORT,DOWN_PIN);
	
	
	// This Following Section is for the external interrupt
	// assigned to the ON/OFF Button.
	
	// Enable Global Interrupt bit
	sei();
	
	// Trigger with Rising Edge
	set_bit(MCUCSR,ISC2);
	
	// Enable INT2 (External Interrupt)
	set_bit(GICR,INT2);
}


/*----------------------------------------------------------------------------*-
UP_pressed() : Check if UP button is pressed or not and return the result.
-*----------------------------------------------------------------------------*/

unsigned char UP_pressed(void){
	// Check if pressed for the first time
	if(!(read_bit(PINB,UP_PIN))){
		// wait for 50 ms to make sure it's pressed (debouncing solution)
		_delay_ms(DEBOUNCE_INTERVAL);
		
		// check one more time
		if (!(read_bit(PINB,UP_PIN))){
			return PRESSED;
		}
		else return NOT_PRESSED;
	}
	else return NOT_PRESSED;	
}

/*----------------------------------------------------------------------------*-
DOWN_pressed() : Check if DOWN button is pressed or not and return the result.
-*----------------------------------------------------------------------------*/

unsigned char DOWN_pressed(void){
	// Check if pressed for the first time
	if(!(read_bit(PINB,DOWN_PIN))){
		// wait for 50 ms to make sure it's pressed (debouncing solution)
		_delay_ms(DEBOUNCE_INTERVAL);
	
		// check one more time
		if (!(read_bit(PINB,DOWN_PIN))){
			return PRESSED;
		}
		else return NOT_PRESSED;
	}
	else return NOT_PRESSED;
}
