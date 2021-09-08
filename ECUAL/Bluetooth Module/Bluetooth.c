/*
 * Bluetooth.c
 *
 * Created: 9/8/2021 1:58:23 PM
 *  Author: Ahmed Nabil
 */ 
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Bluetooth.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define NO_DATA				0U
#define DATA_RECEIVED		1U

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/
volatile uint8_t Blth_DataBuffer[BLTH_BUFFER_SIZE]={0};
volatile uint16_t Blth_DataIndex=0;
volatile uint8_t Blth_RX_Flag = NO_DATA;
/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS LIKE MACROS -*-*-*-*-*-*/
#define Blth_EnableCommand()		Dio_writePin(BLTH_ENABLE_PIN, PIN_HIGH)
#define Blth_EnableData()		 	Dio_writePin(BLTH_ENABLE_PIN, PIN_LOW)

/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

void Blth_receiveCallBack(uint8_t ID)
{
	if(Blth_DataBuffer[Blth_DataIndex-1] == '\r')
	{
		Blth_RX_Flag = DATA_RECEIVED;
	}
	else
	{
		Blth_DataBuffer[Blth_DataIndex] = Uart_DataRegister();
		Blth_DataIndex++;
	}
}

Std_ReturnType Blth_init(void)
{
	Uart_init();
	
	if(BLTH_ROLE_MODE == BLTH_ROLE_MASTER)
	{
		Blth_setMaster();
	}
	else
	{
		Blth_setSlave();
	}
	Uart_EnableNotification_RXC(BLTH_UART_CHANNEL);
	EnableGlobalInterrupts();
	Interrupt_install(USART_RXC_IRQ, Blth_receiveCallBack)
	
	return E_OK;
}

Std_ReturnType Blth_sendData(uint8_t *DataPtr, uint16_t DataSize)
{
	Blth_EnableData();
	Uart_sendPacket(DataPtr, DataSize);
	
	return E_OK;
}

Std_ReturnType Blth_readData(uint8_t *DataPtr)
{
	while (Blth_RX_Flag != DATA_RECEIVED);
	Blth_DataIndex = 0;
	Blth_RX_Flag = NO_DATA;
	arrayCopy(Blth_DataBuffer, DataPtr, Blth_DataIndex);
	DataPtr[Blth_DataIndex+1] = '\0';
	return E_OK;
}

Std_ReturnType Blth_sendCommand(uint8_t* CommandPtr, uint16_t CommandSize)
{
	Blth_EnableCommand();
	
	Uart_sendPacket(CommandPtr, CommandSize);
	
	Blth_EnableData();
	
	return E_OK;
}

Std_ReturnType Blth_RenameDevice(uint8_t *newName)
{
	uint8_t commandFrame[50] = "AT+NAME=";
	
	stringConcatenate(commandFrame, newName);
	uint8_t frameLength = stringLength(commandFrame);
	commandFrame[frameLength-1] = '\r';
	commandFrame[frameLength] = '\n';
	Blth_sendCommand(commandFrame, frameLength+1);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_setSlave(void)
{
	uint8_t commandFrame[11] = "AT+ROLE=0\r\n";
	Blth_sendCommand(commandFrame, 11);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_setMaster(void)
{
	uint8_t commandFrame[11] = "AT+ROLE=1\r\n";
	Blth_sendCommand(commandFrame, 11);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_setBaudRate(uint32_t newBaudRate)
{
	uint8_t commandFrame[22] = "AT+UART=";
	
	uint8_t stringBaudRate[8]={0};
	integerToString(newBaudRate,stringBaudRate,DEC);
	stringConcatenate(commandFrame,stringBaudRate);
	uint8_t frameLength = stringLength(commandFrame);
	commandFrame[frameLength-1] = ',';
	commandFrame[frameLength] = '0';
	commandFrame[frameLength+1] = ',';
	commandFrame[frameLength+2] = '0';
	commandFrame[frameLength+3] = '\r';
	commandFrame[frameLength+4] = '\n';
	Blth_sendCommand(commandFrame, frameLength+5);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	Uart_setBaudRate(newBaudRate);
	
	return E_OK;
}

Std_ReturnType Blth_getBaudRate(uint32_t *currentBaudRate)
{
	uint8_t commandFrame[11] = "AT+UART?\r\n";
	uint8_t receivedFrame[22] = {0};
	uint8_t loopIndex=6;
	uint8_t stringBaudRate[8] = {0};
	
	Blth_sendCommand(commandFrame, 10);
	
	Blth_readData(receivedFrame);
	
	if(receivedFrame[0] != '+')
	{
		return E_NOT_OK;
	}
	
	for(loopIndex=6; loopIndex<22; loopIndex++)
	{
		if(receivedFrame[loopIndex] == ',')
		{
			stringBaudRate[loopIndex-6] = '\0';
			break;
		}
		else
		{
			stringBaudRate[loopIndex-6] = receivedFrame[loopIndex];
		}
	}
	stringToInteger(stringBaudRate, currentBaudRate);
	
	return E_OK;
}

Std_ReturnType Blth_testDevice(void)
{
	uint8_t commandFrame[4] = "AT\r\n";
	Blth_sendCommand(commandFrame, 4);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_getOwnMacAddress(uint8_t *ownMacAddress)
{
	uint8_t commandFrame[10] = "AT+ADDR?\r\n";
	uint8_t receivedFrame[22] = {0};
	uint8_t loopIndex=6, arrayIndex=0;;
	
	Blth_sendCommand(commandFrame, 4);
	Blth_readData(receivedFrame);
	
	if(receivedFrame[0] != '+')
	{
		return E_NOT_OK;
	}
	else
	{
		
	}
	for(loopIndex=6; loopIndex<22; loopIndex++)
	{
		if(receivedFrame[loopIndex] == '\r')
		{
			break;
		}
		else if(receivedFrame[loopIndex] == ':')
		{
		}
		else
		{
			ownMacAddress[arrayIndex] = receivedFrame[loopIndex];
			arrayIndex++;
		}
	}
	ownMacAddress[arrayIndex] = '\0';
	return E_OK;
}

Std_ReturnType Blth_pairDevice(uint8_t *DeviceMacAddress)
{
	Blth_sendCommand((uint8_t*)"AT+CMODE=0\r\n",12);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	uint8_t commandFrame[24] = "AT+BIND=";
	uint8_t loopIndex=0,arrayIndex=8;
	for (loopIndex=0;loopIndex<12;loopIndex++)
	{
		commandFrame[arrayIndex] = DeviceMacAddress[loopIndex];
		if((loopIndex==3) || (loopIndex==5))
		{
			arrayIndex++;
			commandFrame[arrayIndex] = ',';
		}
		arrayIndex++;
	}
	commandFrame[arrayIndex++] = '\r';
	commandFrame[arrayIndex++] = '\n';
	Blth_sendCommand(commandFrame, arrayIndex);
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	return E_OK;
}

Std_ReturnType Blth_setPassword(uint8_t *ownPassword)
{
	uint8_t commandFrame[22] = "AT+PWD=";
	
	stringConcatenate(commandFrame,ownPassword);
	uint8_t frameLength = stringLength(commandFrame);
	commandFrame[frameLength-1] = '\r';
	commandFrame[frameLength] = '\n';
	Blth_sendCommand(commandFrame, frameLength+1);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_checkOK(void)
{
	uint8_t receivedFrame[4] = {0};
	Blth_readData(receivedFrame);
	if ((receivedFrame[0] == 'O')&&(receivedFrame[1] == 'K'))
	{
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
	return E_NOT_OK;
}