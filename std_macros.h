/*
 * std_macros.h
 *
 * Created: 18-Jul-20 6:47:15 PM
 *  Author: Hatem
 */ 


#ifndef STD_MACROS_H_
#define STD_MACROS_H_

// Macros for basic operations
// for bits in a register.

#define set_bit(reg,bit) reg|=(1<<bit)
#define clr_bit(reg,bit) reg&=~(1<<bit)
#define tog_bit(reg,bit) reg^=(1<<bit)
#define read_bit(reg,bit) reg&(1<<bit)
#define is_bit_set(reg,bit) reg&(1<<bit)>>bit
#define is_bit_clr(reg,bit) !(reg&(1<<bit)>>bit)


#endif /* STD_MACROS_H_ */