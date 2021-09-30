 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Symbols.h
 *
 * Description: Header file for Port Module Symbols.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/

#ifndef PORT_SYMBOLS_H_
#define PORT_SYMBOLS_H_

/*
* PORT Ports indices
*/
#define PORT_A_ID		0
#define PORT_B_ID		1
#define PORT_C_ID		2
#define PORT_D_ID		3
#define PORT_E_ID		4
#define PORT_F_ID		5

/*
* PORT A pin indices
*/
#define PORT_A_PIN_0  (uint8)0
#define PORT_A_PIN_1  (uint8)1
#define PORT_A_PIN_2  (uint8)2
#define PORT_A_PIN_3  (uint8)3
#define PORT_A_PIN_4  (uint8)4
#define PORT_A_PIN_5  (uint8)5
#define PORT_A_PIN_6  (uint8)6
#define PORT_A_PIN_7  (uint8)7
/*
* PORT B pin indices
*/
#define PORT_B_PIN_0  (uint8)10
#define PORT_B_PIN_1  (uint8)11
#define PORT_B_PIN_2  (uint8)12
#define PORT_B_PIN_3  (uint8)13
#define PORT_B_PIN_4  (uint8)14
#define PORT_B_PIN_5  (uint8)15
#define PORT_B_PIN_6  (uint8)16
#define PORT_B_PIN_7  (uint8)17
/*
* PORT C pin indices
*/
#define PORT_C_PIN_0  (uint8)20
#define PORT_C_PIN_1  (uint8)21
#define PORT_C_PIN_2  (uint8)22
#define PORT_C_PIN_3  (uint8)23
#define PORT_C_PIN_4  (uint8)24
#define PORT_C_PIN_5  (uint8)25
#define PORT_C_PIN_6  (uint8)26
#define PORT_C_PIN_7  (uint8)27
/*
* PORT D pin indices
*/
#define PORT_D_PIN_0  (uint8)30
#define PORT_D_PIN_1  (uint8)31
#define PORT_D_PIN_2  (uint8)32
#define PORT_D_PIN_3  (uint8)33
#define PORT_D_PIN_4  (uint8)34
#define PORT_D_PIN_5  (uint8)35
#define PORT_D_PIN_6  (uint8)36
#define PORT_D_PIN_7  (uint8)37
/*
* PORT E pin indices
*/
#define PORT_E_PIN_0  (uint8)40
#define PORT_E_PIN_1  (uint8)41
#define PORT_E_PIN_2  (uint8)42
#define PORT_E_PIN_3  (uint8)43
#define PORT_E_PIN_4  (uint8)44
#define PORT_E_PIN_5  (uint8)45
#define PORT_E_PIN_6  (uint8)46
#define PORT_E_PIN_7  (uint8)47
/*
* PORT F pin indices
*/
#define PORT_F_PIN_0  (uint8)50
#define PORT_F_PIN_1  (uint8)51
#define PORT_F_PIN_2  (uint8)52
#define PORT_F_PIN_3  (uint8)53
#define PORT_F_PIN_4  (uint8)54
#define PORT_F_PIN_5  (uint8)55
#define PORT_F_PIN_6  (uint8)56
#define PORT_F_PIN_7  (uint8)57


/*
 **********Port Pin Modes**********
 */
#define PORT_PIN_MODE_DIO                   0U
#define PORT_PIN_MODE_GPT                   1U
#define PORT_PIN_MODE_WDG                   2U
#define PORT_PIN_MODE_MEM                   3U
#define PORT_PIN_MODE_ADC                   4U
#define PORT_PIN_MODE_PWM                   5U
#define PORT_PIN_MODE_SPI0_PORTA            2U
#define PORT_PIN_MODE_SPI1_PORTF            2U
#define PORT_PIN_MODE_SPI1_PORTD            2U
#define PORT_PIN_MODE_SPI2_PORTB            2U
#define PORT_PIN_MODE_SPI3_PORTD            1U
#define PORT_PIN_MODE_ICU                   7U
#define PORT_PIN_MODE_CAN                   8U

#endif /* PORT_SYMBOLS_H_ */
