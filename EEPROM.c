/*
 * EEPROM.c
 *
 * Created: 3/22/2021 6:27:21 PM
 *  Author: Hatem
 */ 

#include "EEPROM.h"

/*----------------------------------------------------------------------------*-
EEPROM_read() : To read the data from the EEPROM given the Address.
-*----------------------------------------------------------------------------*/

unsigned char EEPROM_read(const unsigned short addr){
	// Setup Address Register
	EEARL = (char)addr;
	EEARH = (char)(addr>>8);
	
	// Start Reading
	set_bit(EECR,EERE);
	
	// Return Data
	return EEDR;
}

/*----------------------------------------------------------------------------*-
EEPROM_write() : to write data in the EEPROM given the address and the data.
-*----------------------------------------------------------------------------*/

void EEPROM_write(const unsigned short addr, unsigned char data){
	unsigned char INT_EN=0;
		
	// Setup Address Register
	EEARL = (char)addr;
	EEARH = (char)(addr>>8);
	
	// Put Data in Data Register
	EEDR = data;
	
	// Disable Interrupts to work fine
	if(((SREG&(1<<7))>>7)==1){
		INT_EN = 1;
		clr_bit(SREG,7);
	}
	
	// Start Writing
	set_bit(EECR,EEMWE);
	set_bit(EECR,EEWE);
	while(((EECR&(1<<EEWE))>>EEWE)==1);
	
	// Back
	if (INT_EN==1)
	{
		set_bit(SREG,7);
	}
	
}