/*
 * ModuleTest.c
 *
 *	Provides the testing functions all of individual peripheral testing
 *	and full system testing
 *
 * Created on: 12/4/2024
 *		Author: Omar Fayoumi
 *
 */
 
#include "ModuleTest.h"
#include "TCS34727.h"
#include "MPU6050.h"
#include "UART0.h"
#include "Servo.h"
#include "LCD.h"
#include "I2C.h"
#include "util.h"
#include "ButtonLED.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static char printBuf[100];
static char angleBuf[LCD_ROW_SIZE];
static char colorBuf[LCD_ROW_SIZE];
static char colorString[6];

/* RGB Color Struct Instance */
RGB_COLOR_HANDLE_t RGB_COLOR;
	
/* MPU6050 Struct Instance */
MPU6050_ACCEL_t Accel_Instance;
MPU6050_GYRO_t 	Gyro_Instance;
MPU6050_ANGLE_t Angle_Instance;

const uint8_t color_arr[] = {RED, GREEN, BLUE};
const uint8_t COLOR_MAX = 3;
uint8_t COLOR = 0;
const uint8_t TEST_CASE_MAX = 7;
static void Test_Delay(void){
	/*CODE_FILL*/				//Toggle Red Led
	LEDs = color_arr[COLOR];
	/*CODE_FILL*/				//Delay for 0.5s using millisecond delay
	DELAY_1MS(500);
	LEDs = DARK;
	DELAY_1MS(500);
}

static void Test_UART(void){
	/*CODE_FILL*/						
	// 1. Construct a string with letters, decimal numbers and floats using sprintf
	// 2. Send the string to PC serial terminal for display	
	// 3. Delay for 1s using ms delay function
	char buffer [50] = "%s";
	float fl_value = 0.5;
	int i_value = 10;
	sprintf(buffer, "this is a test %d and %f",  i_value, fl_value);
	UART0_OutString(buffer);
	UART0_OutCRLF();
	DELAY_1MS(1000);
}

static void Test_I2C(void){
	/*CODE_FILL*/						
	/* Check if RGB Color Sensor has been detected and display the ret value on PC serial terminal. */
	uint8_t ret = I2C0_Receive(TCS34727_ADDR, TCS34727_CMD|TCS34727_ID_R_ADDR);
	
	// Return in Hex
	sprintf(printBuf, "ID: %x\r\n", ret);
	UART0_OutString(printBuf);
}


static void Test_MPU6050(void)
{
	char string[50];
	
	/* Grab Accelerometer and Gyroscope Raw Data*/
	MPU6050_ACCEL_t acc;
	MPU6050_GYRO_t gyro;
	MPU6050_ANGLE_t ang; 
	
	/* Process Raw Accelerometer and Gyroscope Data */
	MPU6050_Process_Accel(&acc);
	MPU6050_Process_Gyro(&gyro);
	
	MPU6050_Get_Accel(&acc);
	MPU6050_Get_Gyro(&gyro);
	
	/* Calculate Tilt Angle */
	MPU6050_Get_Angle(&acc, &gyro, &ang);
	
	/* Format buffer to print data and angle */
	sprintf(string, "Accelerometer Data - X: %.2f Y: %.2f Z: %.2f", acc.Ax, acc.Ay, acc.Az);
	UART0_OutString(string);
	UART0_OutCRLF();
	sprintf(string, "Gyroscope Data - X: %.2f Y: %.2f Z: %.2f", gyro.Gx, gyro.Gy, gyro.Gz);
	UART0_OutString(string);
	UART0_OutCRLF();
	sprintf(string, "Angle Data - X: %.2f Y: %.2f Z: %.2f", ang.ArX, ang.ArY, ang.ArZ);
	UART0_OutString(string);

	UART0_OutCRLF();
	UART0_OutCRLF();

	DELAY_1MS(1000);
}

static void Test_TCS34727(void){
	/* Grab Raw Color Data From Sensor */
	/*CODE_FILL*/
	RGB_COLOR_HANDLE_t rgb;
	TCS34727_GET_RGB(&rgb);
	char string[50];
	
	/* Process Raw Color Data to RGB Value */
	/*CODE_FILL*/
	COLOR_DETECTED var = Detect_Color(&rgb);
	/* Change Onboard RGB LED Color to Detected Color */
	switch(var){
		case RED_DETECT:
			LEDs = RED;
			break;
		case GREEN_DETECT:
			LEDs = GREEN;
			break;
		case BLUE_DETECT:
			LEDs = BLUE;
			break;
		case NOTHING_DETECT:
			LEDs = DARK;
			break;
		}
		
	/* Format String to Print */
	/*CODE_FILL*/
		sprintf(string, "R: %.2f G: %.2f B: %.2f", rgb.R, rgb.G, rgb.B);
	/* Print String to Terminal through USB */
	/*CODE_FILL*/
	UART0_OutString(string);
	UART0_OutCRLF();
	DELAY_1MS(1000);
}

static void Test_Servo(void){
	/*
	 * In this test, follow the series of steps below (each step requires a 1s delay after)
	 * 1. Drive Servo to 0 degree
	 * 2. Drive Servo to -45 degree
	 * 3. Drive Servo to 0 degree
	 * 4. Drive Servo to 45 degree
	 * 5. Drive Servo to 0 degree
	 * 6. Drive Servo to -90 degree
	 * 7. Drive Servo to 0 degree
	 * 8. Drive Servo to 90 degree
	 */ 
	Drive_Servo(0);
	DELAY_1MS(1000);
	Drive_Servo(-45);
	DELAY_1MS(1000);
//	Drive_Servo(0);
//	DELAY_1MS(1000);
//	Drive_Servo(45);
//	DELAY_1MS(1000);
//	Drive_Servo(0);
//	DELAY_1MS(1000);
//	Drive_Servo(-90);
//	DELAY_1MS(1000);
//	Drive_Servo(0);
//	DELAY_1MS(1000);
//	Drive_Servo(90);
//	DELAY_1MS(1000);
	
	
	/*CODE_FILL*/
	
}

static void Test_LCD(void){
	/* Print Name to LCD at Center Location */
	LCD_Clear();
	LCD_Set_Cursor(0,4);
	LCD_Print_Str((uint8_t*)"Group");
	DELAY_1MS(2000);
}

static void Test_Full_System(void){
	/* Grab Accelerometer and Gyroscope Raw Data*/
	/*CODE_FILL*/
		
	/* Process Raw Accelerometer and Gyroscope Data */
	/*CODE_FILL*/
		
	/* Calculate Tilt Angle */
	/*CODE_FILL*/
		
	/* Drive Servo Accordingly to Tilt Angle on X-Axis*/
	/*CODE_FILL*/
		
	/* Format buffer to print MPU6050 data and angle */
	/*CODE_FILL*/
		
	/* Grab Raw Color Data From Sensor */
	/*CODE_FILL*/
		
	/* Process Raw Color Data to RGB Value */
	/*CODE_FILL*/
		
	/* Change Onboard RGB LED Color to Detected Color */
	switch(CODE_FILL){
		case RED_DETECT:
			LEDs = RED;
			strcpy(colorString, "RED");
			break;
		case GREEN_DETECT:
			LEDs = GREEN;
			strcpy(colorString, "GREEN");
			break;
		case BLUE_DETECT:
			LEDs = BLUE;
			strcpy(colorString, "BLUE");
			break;
		case NOTHING_DETECT:
			LEDs = DARK;
			strcpy(colorString, "NA");
			break;
	}
		
	/* Format String to Print RGB value*/
	/*CODE_FILL*/
		
	/* Print String to Terminal through USB */
	/*CODE_FILL*/
		
	/* Update LCD With Current Angle and Color Detected */
//	sprintf(angleBuf, "Angle:%0.2f\0", Angle_Instance.ArX);				//Format String to print angle to 2 Decimal Place
//	sprintf(colorBuf, "Color:%s\0", colorString);									//Format String to print color detected

	sprintf(angleBuf, "Angle:%0.2f", Angle_Instance.ArX);				//Format String to print angle to 2 Decimal Place
	sprintf(colorBuf, "Color:%s", colorString);									//Format String to print color detected
	
	/*CODE_FILL*/						//Clear LCD
	/*CODE_FILL*/						//Safety Delay of 2ms
	/*CODE_FILL*/						//Set Cursor to Row 1 Column 0
	/*CODE_FILL*/						//Print angleBuf String on LCD
	/*CODE_FILL*/						//Safety Delay of 2ms
	/*CODE_FILL*/						//Set Cursor to Row 2 Column 1
	/*CODE_FILL*/						//Print colorBuf String on LCD	
		
	DELAY_1MS(20);
}

uint8_t test_case = 0;

void Module_Test(MODULE_TEST_NAME test)
{
	
	
	
	switch(test_case)
	{
		case 0:
			Test_Delay();
			break;
		
		case 1:
			Test_UART();
			break;
		case 2:
			Test_I2C();
		break;
		case 3:
			Test_MPU6050();
			break;
		
		case 4:
			Test_TCS34727();
			break;
		
		case 5:
			Test_Servo();
			break;
		
		case 6:
			Test_LCD();
			break;
			
		case FULL_SYSTEM_TEST:
			Test_Full_System();
			break;
		
		default:
			break;
	}
	
}

void GPIOPortF_Handler(void)
{
	DELAY_1MS(30);
	
	 if(SW1_FLAG)
	{
	 test_case = (test_case + 1) % TEST_CASE_MAX;
	 GPIO_PORTF_ICR_R = SW1_PIN;
	}
	 if(SW2_FLAG)
	{
	 COLOR = (COLOR + 1)% COLOR_MAX;
	 GPIO_PORTF_ICR_R = SW2_PIN;
 }
}