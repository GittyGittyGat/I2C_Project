/*
 * ModuleTest.h
 *
 *	Provides the testing functions all of individual peripheral testing
 *	and full system testing
 *
 * Created on: 12/4/24
 *		Author: Omar Fayoumi
 *
 */
 
typedef enum{
	DELAY_TEST,
	UART_TEST,
	I2C_TEST,
	TCS34727_TEST,
	MPU6050_TEST,
	SERVO_TEST,
	LCD_TEST,
	FULL_SYSTEM_TEST
} MODULE_TEST_NAME;
 
void Module_Test(MODULE_TEST_NAME test);