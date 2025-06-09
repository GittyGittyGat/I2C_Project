/*
 * util.h
 *
 *	Provides basic utility function such as delay and 
 *	value mapping
 *
 * Created on: 12/4/2024
 *		Author: Omar Fayoumi
 *
 */
 

#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#define CONSTANT_FILL	(0)     // a place holder for all constants needs to be defined by students
#define CODE_FILL	(0)     // a place holder for code needs to be defined by students

/* List of Fill In Macros */
#define EN_WTIMER0_CLOCK			(0x01)
#define WTIMER0_TAEN_BIT			(0x01)
#define WTIMER0_32_BIT_CFG		(0x4)
#define WTIMER0_PERIOD_MODE		(0x2)
#define PRESCALER_VALUE				(16000)

void WTIMER0_Init(void);
void DELAY_1MS(uint32_t);
int16_t map(int16_t, int16_t, int16_t, int16_t, int16_t);

#endif