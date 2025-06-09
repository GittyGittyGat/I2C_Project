/*
 * LCD.c
 *
 *	Main Implementation of LCD functions such as initialization, sending
 *	commands and data, and basic functionalities
 *
 * Created on: 12/4/24
 *		Author: Omar Fayoumi
 *
 */
 
#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "util.h"
#include "I2C.h"

/*
 *	-------------------LCD_Send_CMD------------------
 *	Local LCD send commands function
 *	Input: Command to send
 *	Output: None
 */
static void LCD_Send_CMD(uint8_t cmd){
	
	/* Temp Variables to hold upper and lower value */
	uint8_t cmd_upper, cmd_lower;
	uint8_t cmd_array[4];								//Command Array to Burst Transmit
	
	/* Seperate Upper and Lower Nibble */
	cmd_upper = UPPER_NIBBLE_MSK & cmd; // use UPPER_NIBBLE_MSK here
	cmd_lower = UPPER_NIBBLE_MSK & (cmd << NIBBLE_SHIFT); // use UPPER_NIBBLE_MSK here
	
	/* LCD I2C Message Pattern */
	cmd_array[0] = cmd_upper | (BACKLIGHT|EN_Pin);
	cmd_array[1] = cmd_upper | BACKLIGHT;
	cmd_array[2] = cmd_lower | (BACKLIGHT|EN_Pin);
	cmd_array[3] = cmd_lower | BACKLIGHT;
	
	/* I2C Burst Transmit Command Array to LCD */
	I2C0_Burst_Transmit(LCD_WRITE_ADDR, PCF8574A_REG, cmd_array, sizeof(cmd_array));
}

/*
 *	------------------LCD_Send_Data------------------
 *	Local LCD send data function
 *	Input: Data to send
 *	Output: None
 */
static void LCD_Send_Data(uint8_t data){
	
	/* Temp Variables to hold upper and lower value */
	uint8_t data_upper, data_lower;
	uint8_t data_array[4];							//Data Array to Burst Transmit
	
	/* Seperate Upper and Lower Nibble */
	data_upper = UPPER_NIBBLE_MSK & data; // use UPPER_NIBBLE_MSK here
	data_lower = UPPER_NIBBLE_MSK & (data << NIBBLE_SHIFT); // use UPPER_NIBBLE_MSK here
	
	/* LCD I2C Message Pattern */
	data_array[0] = data_upper | (BACKLIGHT|EN_Pin|RS_Pin);
	data_array[1] = data_upper | (BACKLIGHT|RS_Pin);
	data_array[2] = data_lower | (BACKLIGHT|EN_Pin|RS_Pin);
	data_array[3] = data_lower | (BACKLIGHT|RS_Pin);
	
	/* I2C Burst Transmit Data Array to LCD */
	I2C0_Burst_Transmit(LCD_WRITE_ADDR, PCF8574A_REG, data_array, sizeof(data_array));
}

/*
 *	-------------------LCD_Init------------------
 *	Basic LCD Initialization Function
 *	Input: None
 *	Output: None
 */
void LCD_Init(void){
	
	/* Magic LCD Initialization */
	DELAY_1MS(50);
	LCD_Send_CMD(INIT_REG_CMD);
	DELAY_1MS(5);
	LCD_Send_CMD(INIT_REG_CMD);
	DELAY_1MS(1);
	LCD_Send_CMD(INIT_REG_CMD);
	DELAY_1MS(10);
	LCD_Send_CMD(INIT_FUNC_CMD);
	DELAY_1MS(10);
	
	/* 4-Bit Display Mode Initialization */
	//Set Function to 4-Bit, 2 rows, and 5x8 Character
	LCD_Send_CMD(FUNC_MODE|FUNC_4_BIT|FUNC_2_ROW|FUNC_5_7);
	DELAY_1MS(1);
	
	//Turn off Display
	LCD_Send_CMD(DISP_CMD|DISP_OFF|DISP_CURSOR_OFF|DISP_BLINK_OFF);
	DELAY_1MS(1);
	
	//Clear Display
	LCD_Send_CMD(CLEAR_DISP_CMD);
	DELAY_1MS(2);
	
	//Set Entry Mode
	LCD_Send_CMD(ENTRY_MODE_CMD|ENTRY_INC_CURSOR);
	DELAY_1MS(1);
	
	//Turn on Display with cursor and blink enable
	LCD_Send_CMD(DISP_CMD|DISP_ON|DISP_CURSOR_ON|DISP_BLINK_ON);
	
}

/*
 *	-------------------LCD_Clear------------------
 *	Clear the LCD Display by passing a command
 *	Input: None
 *	Output: None
 */
void LCD_Clear(void){
	LCD_Send_CMD(CLEAR_DISP_CMD);
	DELAY_1MS(1);
}

/*
 *	----------------LCD_Set_Cursor----------------
 *	Set Cursor to Desire Place
 *	Input: Desired Row and Column to place Cursor
 *	Output: None
 */
void LCD_Set_Cursor(uint8_t row, uint8_t col){
	
	/* Switch case based of row choice */
	switch(row){
		case ROW1:
			col |= FIRST_ROW_CMD;
			break;
		case ROW2:
			col |= SECOND_ROW_CMD;
			break;
		default:
			col |= FIRST_ROW_CMD;
			break;
	}
	
	/* Send Command to set Row and Column */
	LCD_Send_CMD(col);
	DELAY_1MS(2);
	
}

/*
 *	---------------LCD_Reset_Cursor---------------
 *	Reset Cursor back to Row 1 and Column 0
 *	Input: None
 *	Output: None
 */
void LCD_Reset_Cursor(void){
	LCD_Send_CMD(RETURN_HOME_CMD);
	DELAY_1MS(1);
}

/*
 *	----------------LCD_Print_Char----------------
 *	Prints a Character to LCD
 *	Input: Character Hex Value
 *	Output: None
 */
void LCD_Print_Char(uint8_t data){
	LCD_Send_Data(data);
	DELAY_1MS(1);
}

/*
 *	----------------LCD_Print_Str-----------------
 *	Prints a string to LCD
 *	Input: Pointer to Character Array
 *	Output: None
 */
void LCD_Print_Str(uint8_t* str){
	while(*str){
		LCD_Send_Data(*str++);
		DELAY_1MS(2);
	}
}
