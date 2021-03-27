/*
 * Sys.c
 *
 * Created: 3/22/2021 10:05:58 AM
 *  Author: Hatem
 */ 

/*----------------------------------------------------------------------------*-
sys_init() : to initialize system by initializing all modules, and setting the
initial temperature to the EEPROM.
-*----------------------------------------------------------------------------*/

#include "Sys.h"

void sys_init(void){
	// Modules initialization
	ADC_init();
	Buttons_init();
	cool_init();
	heat_init();
	led_init();
	SSD_init();
	timer0_init();
	timer1_init();
	timer1_INT_enable();
	
	// ON_OFF_flag is in OFF mode initially
	Curr_state = OFF;
	
	// setting initial temp. and fill array
	if(EEPROM_read(0x0000) != 0xFF){
		desired_temp = EEPROM_read(0x0000);
	}
	else{
		desired_temp = INIT_DESIRED_TEMP;
	}
	
	temp_arr_init();
	
	// Save desired temp in EEPROM
	// which is the INIT_DESIRED_TEMP.
	EEPROM_write(0x0000,(uint8_t) desired_temp);	
	
}

/*----------------------------------------------------------------------------*-
OFF_state() : This turns off all output display peripherals, and the Timer.
-*----------------------------------------------------------------------------*/

void OFF_state(void){
		SSD_turn_off();
		led_off();
		heat_stop();
		cool_stop();
		go_to_sleep();
}

/*----------------------------------------------------------------------------*-
ON_state : This is the working state where it does the following:
	- waits for the timer to measure temperature using ADC every 100ms.
	- checks for the UP and DOWN buttons to switch to the SETTING mode.
-*----------------------------------------------------------------------------*/

void ON_state(void){
	
	// if 100ms elapsed and flag is triggered
	// measure temperature from the sensor
	// add it to array and get the average
		
	if (temp_measure_f == 1){
		actual_temp = (ADC_read()*0.5);
		add_new_temp(temp_arr , actual_temp);
		avg_temp = calc_avg_temp(temp_arr);	
		temp_measure_f = 0;
	}
	
	SSD_write(actual_temp);
	
	// turn cooler or heater ON and OFF depending on
	// the average temperature measured from the array.
	
	change_temp();
	 
	 // Check if UP or DOWN buttons are pressed to
	 // switch to the SETTING_MODE
	
	if(UP_pressed()==PRESSED || DOWN_pressed()==PRESSED){

		SSD_disable();
		setting_counter = 0;
		Curr_state = SETTING;
			
	}
}

/*----------------------------------------------------------------------------*-
Setting_state : 
-*----------------------------------------------------------------------------*/

void SET_state(void){
	heat_stop();
	cool_stop();
	led_off();
	
	// to toggle the seven segment
	// while writing the desired temperature
	
	if(toggle_f == 1){
		SSD_write(desired_temp);
	}
	else{
		SSD_turn_off();
	}
	
	// if UP or DOWN pressed, change the desired temp
	// as long as it's still in range
	
	if((UP_pressed() == PRESSED) && (desired_temp < MAX_TEMP)){
		desired_temp = desired_temp + 5;
		setting_counter = 0;
		SSD_write(desired_temp);
	}
	else if ((DOWN_pressed() == PRESSED) && (desired_temp > MIN_TEMP)){
		desired_temp = desired_temp - 5;
		setting_counter = 0;
		SSD_write(desired_temp);
	}
	
	EEPROM_write(0x0000,desired_temp);
	
}

/*----------------------------------------------------------------------------*-
change_temp : This function turns on the Heater or the Cooler
-*----------------------------------------------------------------------------*/

void change_temp(void){
	if( (desired_temp < avg_temp + MARGIN_TEMP) && (desired_temp > avg_temp - MARGIN_TEMP) ){
		// Actual Temperature equals Desired Temperature
		// No need for Heating or Cooling
		heat_stop();
		cool_stop();
		led_off();
	}
	else if(desired_temp < avg_temp + MARGIN_TEMP){
		// Actual Temperature is Larger
		// we need the Cooling element
		
		heat_stop();
		cool_start();
		led_on();
	}
	else if (desired_temp > avg_temp - MARGIN_TEMP){
		// Actual Temperature is Smaller
		// we need the Heating element
		
		heat_start();
		cool_stop();
		if (toggle_f == 1)
		{
			led_on();
		}
		else {
			led_off();
		}
	}
}

/*----------------------------------------------------------------------------*-
temp_array_initialization : This function is a part of the Sys_init. function
that reads the first actual temperature and put it at all elements in the
temperature array.
-*----------------------------------------------------------------------------*/

void temp_arr_init(void){
	uint16_t first_temp = ADC_read()*0.5;
	
	for (uint8_t i = 0; i<NUM_OF_TEMP_MEASURES; i++){
		temp_arr[i]= first_temp;
	}
	
	avg_temp = calc_avg_temp(temp_arr);
	arr_counter = 0;
}

/*----------------------------------------------------------------------------*-
add_new_temp : This function is used to add the new measured temperature to
the temperature array that will have its average during the code.
-*----------------------------------------------------------------------------*/

void add_new_temp(uint16_t * arr , uint16_t new_val){
	arr[arr_counter] = new_val;
	arr_counter ++;
	
	if (arr_counter == 10){
		arr_counter = 0;
	}
}

/*----------------------------------------------------------------------------*-
Calculate_Average_Temp.: to calculate the last 10 measured temperatures.
-*----------------------------------------------------------------------------*/

uint16_t calc_avg_temp(uint16_t * arr){
	uint16_t sum = 0;
	uint16_t avg;
	
	for(uint8_t i=0; i<NUM_OF_TEMP_MEASURES; i++){
		sum = sum + arr[i];
	}
	avg = (uint16_t) sum / NUM_OF_TEMP_MEASURES;
	return avg;
}

/*----------------------------------------------------------------------------*-
go_to_sleep : This function is to keep the CPU in the idle mode to save more
power when it doesn't need to do any task at the moment.
-*----------------------------------------------------------------------------*/

void go_to_sleep(void){
	
	MCUCR&=~(1<<SM0);
	MCUCR&=~(1<<SM1);
	MCUCR&=~(1<<SM2);
	
	MCUCR|=(1<<SE);

}