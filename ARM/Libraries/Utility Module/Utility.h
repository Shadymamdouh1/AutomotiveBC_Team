/*****************************************************************************
* Module: Utility Module
* File Name: Utility.h
* Description: Source file for Utility Module
* Author: Mohamed Magdy
* Date: 23-July-2021
******************************************************************************/

#ifndef UTILITY_H_
#define UTILITY_H_

#include "../../Microcontroller/Std_Types.h"

#define DEC		0
#define HEX		1	
#define BIN		2

#define END_OF_STRING '\0'
#define NEW_LINE	  '\r'
#define BACK_SPACE	  '\b'

uint16 String_3ByteHexAddress_ToDecimal(uint8* u8_tempAddress);

void integerToString(uint16 u16_Num, uint8 *pu8_String, uint8 u8_base);
void stringToInteger(uint8* au8_string, uint32* u32_integer);

uint32 nPowerM(uint32 n, uint32 m);

uint8 stringCmp(uint8 * str1, uint8 * str2);

void separateInteger(uint8* pau8_floatString, uint8* pau8_integerString, uint16 u16_lengthToStop);
void separateDecimal(uint8* pau8_floatString, uint8* pau8_decimalString, uint16 u16_lengthToStart,  uint16 u16_floatArraySize);

uint8 stringLength(uint8* string);
float32 stringToFloat(uint8* string);
void floatToString(float32 f32_num, uint8* string);


void stringConcatenate(uint8* destination, uint8* source);

void stringCopy(uint8* source, uint8* destination);
uint8 Max_String_Num(uint8* string1, uint8* string2);
void EmptyString(uint8 *string);
void stringHexToNum(uint8 *pu8_String, uint16 *pu16_Num);


#endif /* UTILITY_H_ */
