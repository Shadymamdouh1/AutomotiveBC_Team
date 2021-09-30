 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Regs.h
 *
 * Description: Header file for Port Module Registers.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/



#ifndef PORT_REGS_H_
#define PORT_REGS_H_

#include "Std_Types.h"
#include "Port_Symbols.h"

#define     __I     volatile const       /*!< Defines 'read only' permissions                 */
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

typedef volatile uint32 * const M4_PrefRegType;

/*
 * This Partition is intended to be the responsible of the MCU Module.
 * MCU Module is responsible for the clock connection to all the peripherals.
 */
#define M4_PREF_BASE_ADD 			0xE000E000
#define SYS_CTRL_BASE_ADDRESS       0x400FE000
#define RCGCGPIO_REG     			*((M4_PrefRegType)(SYS_CTRL_BASE_ADDRESS + 0x608))

/*
 * Total number of ports on the platform
 */
#define PORTS_NUM	 6u

/*
 * Base address of each port in the memory
 */
#define PORTA_BASE_ADDRESS		0x40004000
#define PORTB_BASE_ADDRESS	    0x40005000
#define PORTC_BASE_ADDRESS 		0x40006000
#define PORTD_BASE_ADDRESS 		0x40007000
#define PORTE_BASE_ADDRESS 		0x40024000
#define PORTF_BASE_ADDRESS 		0x40025000

static uint32 PortsBaseAddressLut[PORTS_NUM] =
{   PORTA_BASE_ADDRESS,
    PORTB_BASE_ADDRESS,
    PORTC_BASE_ADDRESS,
    PORTD_BASE_ADDRESS,
    PORTE_BASE_ADDRESS,
    PORTF_BASE_ADDRESS
};

/*
 * Structure for all the registers of the port
 */
typedef struct
{
    __I  uint32 RESERVED0[255];
    __IO uint32 DATA;                     /*Port Data*/
    __IO uint32 DIR;                      /*Port Direction*/
    __IO uint32 IS;                       /*Port Interrupt Sense*/
    __IO uint32 IBE;                      /*Port Interrupt Both Edges*/
    __IO uint32 IEV;                      /*Port Interrupt Event*/
    __IO uint32 IM;                       /*Port Interrupt Mask*/
    __IO uint32 RIS;                      /*Port Raw Interrupt Status*/
    __IO uint32 MIS;                      /*Port Masked Interrupt Status*/
    __O  uint32 ICR;                       /*Port Interrupt Clear*/
    __IO uint32 AFSEL;                    /*Port Alternate Function Select*/
    __I  uint32 RESERVED1[55];
    __IO uint32 DR2R;                     /*Port 2-mA Drive Select*/
    __IO uint32 DR4R;                     /*Port 4-mA Drive Select*/
    __IO uint32 DR8R;                     /*Port 8-mA Drive Select*/
    __IO uint32 ODR;                      /*Port Open Drain Select*/
    __IO uint32 PUR;                      /*Port Pull-Up Select*/
    __IO uint32 PDR;                      /*Port Pull-Down Select*/
    __IO uint32 SLR;                      /*Port Slew Rate Control Select*/
    __IO uint32 DEN;                      /*Port Digital Enable*/
    __IO uint32 LOCK;                     /*Port Lock*/
    __IO uint32 CR;                        /*Port Commit*/
    __IO uint32 AMSEL;                    /*Port Analog Mode Select*/
    __IO uint32 PCTL;                     /*Port Port Control*/
    __IO uint32 ADCCTL;                   /*Port ADC Control*/
    __IO uint32 DMACTL;                   /*Port DMA Control*/
} Port_MapType;

#define PORT(ID)    ((Port_MapType*)PortsBaseAddressLut[ID])

#define PORT_A_MAP		PORT(PORT_A_ID)
#define PORT_B_MAP		PORT(PORT_B_ID)
#define PORT_C_MAP		PORT(PORT_C_ID)
#define PORT_D_MAP		PORT(PORT_D_ID)
#define PORT_E_MAP		PORT(PORT_E_ID)
#define PORT_F_MAP		PORT(PORT_F_ID)

#define GPIO_PORT_UNLOCK_VALUE 0x4C4F434B



#endif /* PORT_REGS_H_ */
