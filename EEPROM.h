/*
 * EEPROM.h
 *
 * Created: 3/22/2021 6:27:32 PM
 *  Author: Hatem
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include "std_macros.h"

void EEPROM_write(const unsigned short addr, unsigned char data);
unsigned char EEPROM_read(const unsigned short addr);

#endif /* EEPROM_H_ */