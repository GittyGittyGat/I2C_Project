/*
 * LCD.h
 *
 *	Provides LCD functions such as initialization, sending
 *	commands and data, and basic functionalities
 *
 * Created on: 12/4/24
 *		Author: Omar Fayoumi
 *
 */
 
#ifndef LCD_H_
#define LCD_H_
#include "util.h"

/*************PCF8574A Register*************/
#define LCD_WRITE_ADDR			(0x3FU)
#define PCF8574A_REG				(0x00U)

/**************LCD CMD Register*************/
#define INIT_REG_CMD				(0x30U)
#define INIT_FUNC_CMD				(0x20U)

#define FUNC_MODE						(0x20)
	#define FUNC_4_BIT				(0)
	#define FUNC_2_ROW				(0x08)
	#define FUNC_5_7					(0)
	
#define DISP_CMD						(0x08)
	#define DISP_ON						(0x04)
	#define DISP_OFF					(0)
	#define DISP_CURSOR_ON		(0x02)
	#define DISP_CURSOR_OFF		(0)
	#define DISP_BLINK_ON			(0x01)
	#define DISP_BLINK_OFF		(0)
	
#define CLEAR_DISP_CMD			(0x01)

#define ENTRY_MODE_CMD			(0x04)
	#define ENTRY_INC_CURSOR	(0x02)
//	#define ENTRY_DISP_SHIFT	()
	
#define RETURN_HOME_CMD			(0x02)

#define FIRST_ROW_CMD				(0x00)
#define SECOND_ROW_CMD			(0x40)

/* LCD Module Macros */
#define RS_Pin							(0x01)
#define RW_Pin							(0x02)
#define EN_Pin							(0x04)
#define BACKLIGHT						(0x08)

/* General Macros */
#define UPPER_NIBBLE_MSK		(0xF0)
#define NIBBLE_SHIFT				(4)
#define ROW1								(0U)
#define ROW2								(1U)
#define LCD_ROW_SIZE				(16)

#include <stdint.h>

/*
 *	-------------------LCD_Init------------------
 *	Basic LCD Initialization Function
 *	Input: None
 *	Output: None
 */
void LCD_Init(void);

/*
 *	-------------------LCD_Clear------------------
 *	Clear the LCD Display by passing a command
 *	Input: None
 *	Output: None
 */
void LCD_Clear(void);

/*
 *	----------------LCD_Set_Cursor----------------
 *	Set Cursor to Desire Place
 *	Input: Desired Row and Column to place Cursor
 *	Output: None
 */
void LCD_Set_Cursor(uint8_t row, uint8_t col);

/*
 *	---------------LCD_Reset_Cursor---------------
 *	Reset Cursor back to Row 1 and Column 0
 *	Input: None
 *	Output: None
 */
void LCD_Reset_Cursor(void);

/*
 *	----------------LCD_Print_Char----------------
 *	Prints a Character to LCD
 *	Input: Character Hex Value
 *	Output: None
 */
void LCD_Print_Char(uint8_t data);

/*
 *	----------------LCD_Print_Str-----------------
 *	Prints a string to LCD
 *	Input: Pointer to Character Array
 *	Output: None
 */
void LCD_Print_Str(uint8_t* str);

#endif