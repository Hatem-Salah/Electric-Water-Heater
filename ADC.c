/*
 * ADC.c
 *
 * Created: 3/22/2021 9:29:36 AM
 *  Author: Hatem
 */ 

#include "ADC.h"

/*----------------------------------------------------------------------------*-
ADC_init() : to initialize the ADC to sense temperature from the sensor connected.
-*----------------------------------------------------------------------------*/

void ADC_init(){
	
	// Choosing reference voltage option.
	// the AVCC pin with a capacitor at the AREF pin.
	set_bit(ADMUX,REFS0);
	
	// Choosing Channel One (Single Ended In.) at A0 pin.
	clr_bit(ADMUX,MUX0);
	clr_bit(ADMUX,MUX1);
	clr_bit(ADMUX,MUX2);
	clr_bit(ADMUX,MUX3);
	clr_bit(ADMUX,MUX4);
	
	// Choosing the Data to be Right Adjusted in the Data Reg.
	clr_bit(ADMUX,ADLAR);
	
	// Choosing Prescaler for the ADC clock.
	// the following is choosing (2) as a Prescaler.
	set_bit(ADCSRA,ADPS0);
	clr_bit(ADCSRA,ADPS1);
	clr_bit(ADCSRA,ADPS2);
	
	// Enable the ADC
	set_bit(ADCSRA,ADEN);
	
}

/*----------------------------------------------------------------------------*-
ADC_read() : to read data from the temperature sensor whenever it's called.
-*----------------------------------------------------------------------------*/

uint16_t ADC_read(){
	
	uint16_t data;
	
	// Start Conversion
	set_bit(ADCSRA,ADSC);
	
	// Wait for flag to be set.
	// Indication of finished conversion
	while(is_bit_clr(ADCSRA,ADIF));
	
	// Read Data from the ADC Data Register
	// Read the Low register first!
	data = ADCL;
	data |= (ADCH<<8);
	
	// Clear Flag (As we are not using the interrupt)
	// It won't be cleared automatically!
	set_bit(ADCSRA,ADIF);
	
	return data;	
}