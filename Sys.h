/*
 * Sys.h
 *
 * Created: 3/22/2021 10:06:13 AM
 *  Author: Hatem
 */ 


#ifndef SYS_H_
#define SYS_H_


// Description
/*
The system is using a modified cooperative scheduler. it has
only one task (ON_TASK) which executes the functionality of
the normally working WATER HEATER. the ON_TASK is also checking
if buttons are pressed so it can switch to the SETTING_MODE, 
which is another function (state) to allow the user to change
the set point - or the desired temperature.
*/

// when Reading the ADC, the value is halved due to some issues
// to the Temperature sensor in Proteus LM35. So, please, configure
// it depending on your sensor.

// Including All Peripherals
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Sys_Config.h"
#include "std_macros.h"
#include "ADC.h"
#include "Buttons.h"
#include "Cool_Heat_Elements.h"
#include "LED.h"
#include "SSD_disp.h"
#include "Timer.h"
#include "EEPROM.h"

#define OFF 0
#define ON 1
#define SETTING 2

/**************************************** 
*               Functions               *
****************************************/

void sys_init(void);
void ON_state(void);
void OFF_state(void);
void SET_state(void);

void change_temp(void);
void add_new_temp(uint16_t * arr , uint16_t new_val);
uint16_t calc_avg_temp(uint16_t * arr);
void temp_arr_init(void);
void go_to_sleep(void);

/****************************************
*               Variables               *
****************************************/

// will add as needed

uint8_t Curr_state;

uint16_t temp_arr[NUM_OF_TEMP_MEASURES];
uint16_t desired_temp;
uint16_t actual_temp;
uint16_t avg_temp;

uint8_t temp_measure_f;
uint8_t temp_measure_counter;
uint8_t setting_counter;

uint16_t toggle_f;
uint8_t arr_counter;

#endif /* SYS_H_ */