/*
 * I2CTestMain.c
 *
 *	Test the basic functionality of I2C by reading and writing to the 
 *	TCS34727 RGB Sensor and MPU6050 6-dof IMU, as well as controlling
 *	a Servo Motor and a 16x2 LCD 
 *
 * Created on: 12/4/2024
 *		Author: Omar fayoumi
 *
 */
 
#include "tm4c123gh6pm.h"
#include "I2C.h"
#include "UART0.h"
#include "TCS34727.h"
#include "MPU6050.h"
#include "ButtonLED.h"
#include "util.h"
#include "Servo.h"
#include "LCD.h"
#include <stdio.h>
#include <string.h>
#include "ModuleTest.h"

/* List of Predefined Macros for individual Peripheral Testing */
#define DELAY
#define UART
#define I2C
#define TCS34727
#define MPU6050
#define SERVO
#define LCD
//#define FULL_SYSTEM

int main(void){
	
	/* Peripheral Initialization */
	UART0_Init();
	LED_Init();
	BTN_Init();
	
	#if defined(DELAY) || defined(TCS34727) || defined(MPU6050) || defined(LCD) || defined(FULL_SYSTEM)	
	WTIMER0_Init();
	#endif
	
	#if defined (I2C) || defined(TCS34727) || defined(MPU6050) || defined(LCD) || defined(FULL_SYSTEM)
	I2C0_Init();
	#endif
	
	#if defined(TCS34727) || defined(FULL_SYSTEM)
	/* Color Sensor Initialization */
	TCS34727_Init();
	#endif
	
	#if defined(MPU6050) || defined(FULL_SYSTEM)
	/* MPU6050 Initialization */
	MPU6050_Init();
	#endif
	
	#if defined(SERVO) || defined(FULL_SYSTEM)
	/* Servo Initialization */
	Servo_Init();
	#endif
	
	#if defined(LCD) || defined(FULL_SYSTEM)
	/* LCD Initialization */
	LCD_Init();
	#endif
	
	while(1){
		
		#ifdef DELAY
		Module_Test(DELAY_TEST);
		#endif
		
		#ifdef UART
		Module_Test(UART_TEST);
		#endif
		
		#ifdef I2C
		Module_Test(I2C_TEST);
		#endif
		
		#ifdef MPU6050
		Module_Test(MPU6050_TEST);
		#endif
		
		#ifdef TCS34727
		Module_Test(TCS34727_TEST);
		#endif
		
		#ifdef SERVO
		Module_Test(SERVO_TEST);
		#endif
		
		#ifdef LCD
		Module_Test(LCD_TEST);
		#endif
		
		#ifdef FULL_SYSTEM
		Module_Test(FULL_SYSTEM_TEST);
		#endif
		
	}
	
	return 0;
}
