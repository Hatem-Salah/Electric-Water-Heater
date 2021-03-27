/*
 * Button.h
 *
 * Created: 3/20/2021 7:00:25 PM
 *  Author: Hatem
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "std_macros.h"

#define PRESSED 1
#define NOT_PRESSED 0

#define DEBOUNCE_INTERVAL 100
#define B_PORT PORTB
#define B_PORT_DIR DDRB

#define ON_OFF_PIN 2
#define UP_PIN 1
#define DOWN_PIN 3

// Buttons Reading Functions
void Buttons_init(void);
void ON_OFF_EXTI(void);

unsigned char UP_pressed(void);
unsigned char DOWN_pressed(void);


#endif /* BUTTON_H_ */