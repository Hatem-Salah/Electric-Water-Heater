/*
 * ssd.c
 *
 * Created: 3/20/2021 5:59:12 PM
 *  Author: Hatem
 */ 

#include "SSD_disp.h"

/*----------------------------------------------------------------------------*-
SSD_Init. : to initialize the Seven Segment by making its port OUTPUT.
-*----------------------------------------------------------------------------*/

// Array for Numbers' Values
uint8_t Nums[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void SSD_init(void){
	
	// setting Seven Segment Pins as output pins
	SSD_PORT_DIR = 0xFF;
	set_bit(SSD_ENABLE_PORT_DIR,SSD1_ENABLE_PIN);
	set_bit(SSD_ENABLE_PORT_DIR,SSD2_ENABLE_PIN);
	
	// Seven Segment initially OFF
	SSD_disable();
	
}
	
/*----------------------------------------------------------------------------*-
SSD_Send. : to Upload data (Number) to the Seven Segment.
-*----------------------------------------------------------------------------*/
	
void SSD_send(uint16_t N){
	SSD_DATA = Nums[N];
}

/*----------------------------------------------------------------------------*-
SSD_enable() : the 2 seven seg. are multiplexed and works with the same pins.
So, this function is to enable one and disable the other.
-*----------------------------------------------------------------------------*/

void SSD_enable(uint8_t disp){
	if(disp == 1){
		set_bit(SSD_ENABLE_PORT,SSD1_ENABLE_PIN);
		clr_bit(SSD_ENABLE_PORT,SSD2_ENABLE_PIN);
	}
	else if (disp == 2){
		set_bit(SSD_ENABLE_PORT,SSD2_ENABLE_PIN);
		clr_bit(SSD_ENABLE_PORT,SSD1_ENABLE_PIN);
	}
}

/*----------------------------------------------------------------------------*-
SSD_disable() : To disable the two seven segments for some special cases.
-*----------------------------------------------------------------------------*/

void SSD_disable(void){
	clr_bit(SSD_ENABLE_PORT,SSD1_ENABLE_PIN);
	clr_bit(SSD_ENABLE_PORT,SSD2_ENABLE_PIN);
}

/*----------------------------------------------------------------------------*-
SSD_turn_off() : To turn off the Seven Segment in the OFF STATE.
-*----------------------------------------------------------------------------*/

void SSD_turn_off(void){
	SSD_DATA = 0x00;
}

/*----------------------------------------------------------------------------*-
SSD_write() : To calculate what to write on each of the two SSDs, and send.
-*----------------------------------------------------------------------------*/

void SSD_write(uint16_t N){
	uint8_t units;
	uint8_t tens;
	
	units = N % 10;
	tens = (int) N / 10;
	
	SSD_enable(DISP1);
	SSD_send(units);
	_delay_ms(5);
	
	SSD_enable(DISP2);
	SSD_send(tens);
	_delay_ms(5);
}