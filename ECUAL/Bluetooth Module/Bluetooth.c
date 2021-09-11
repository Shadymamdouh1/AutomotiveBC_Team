/*
 * Bluetooth.c
 *
 * Created: 9/8/2021 1:58:23 PM
 *  Author: Ahmed Nabil
 */ 
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Bluetooth.h"
#include "Microcontroller/Delay Module/Delay.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define NO_DATA				0U
#define DATA_RECEIVED		1U
#define BLTH_COMMAND_MODE			0U
#define BLTH_DATA_MODE				1U
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/
volatile uint8_t Blth_DataBuffer[BLTH_BUFFER_SIZE]={0};
volatile uint16_t Blth_DataIndex=0;
volatile uint8_t Blth_RX_Flag = NO_DATA;
static uint8_t Blth_CurrentState = BLTH_DATA_MODE;
/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS LIKE MACROS -*-*-*-*-*-*/
#define Blth_Cmd()					Dio_writePin(BLTH_ENABLE_PIN, PIN_HIGH)
#define Blth_Data()		 			Dio_writePin(BLTH_ENABLE_PIN, PIN_LOW)
#define Blth_powerON()				Dio_writePin(BLTH_POWER_PIN,PIN_HIGH)
#define Blth_powerOFF()				Dio_writePin(BLTH_POWER_PIN, PIN_LOW)
/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

void Blth_receiveCallBack(uint8_t ID)
{
	Blth_DataBuffer[Blth_DataIndex] = Uart_DataRegister();
	if(Blth_DataBuffer[Blth_DataIndex] == '\r')
	{
		Blth_RX_Flag = DATA_RECEIVED;
		Blth_DataBuffer[Blth_DataIndex+1]='\0';
	}
	else
	{
	}
	Blth_DataIndex++;
}

Std_ReturnType Blth_EnableCommandMode(void)
{
	Blth_powerOFF();
	Blth_Cmd();
	Blth_powerON();
	Blth_CurrentState = BLTH_COMMAND_MODE;
	
	return E_OK;
}

Std_ReturnType Blth_EnableDataMode(void)
{
	Blth_powerOFF();
	Blth_Data();
	Delay_ms(5);
	Blth_powerON();
	Blth_CurrentState = BLTH_DATA_MODE;
	
	return E_OK;
}

Std_ReturnType Blth_init(void)
{
	Dio_init(strDio_pins);
	Uart_init();
	
	Uart_EnableNotification_RXC(BLTH_UART_CHANNEL);
	EnableGlobalInterrupts();
	Interrupt_install(USART_RXC_IRQ, Blth_receiveCallBack);
	
	return E_OK;
}

Std_ReturnType Blth_sendData(uint8_t *DataPtr)
{	
	/*- Check if it is in command mode -*/
	if(Blth_CurrentState == BLTH_COMMAND_MODE)
	{	
		/*- Change to Data Mode -*/
		Blth_EnableDataMode();
	}
	else
	{
		
	}
	uint8_t dataLength = stringLength(DataPtr);
	DataPtr[dataLength-1] = '\r';
	Uart_sendPacket(DataPtr, );
	
	return E_OK;
}

Std_ReturnType Blth_readData(uint8_t *DataPtr)
{
	/*- Wait for the data to be received -*/
	while (Blth_RX_Flag != DATA_RECEIVED);
	Blth_RX_Flag = NO_DATA; /*- Clear the flag -*/
	/*- Copy the data received to the given data pointer -*/
	stringCopy((uint8_t*)Blth_DataBuffer,DataPtr);
	/*- Clear the buffer -*/
	EmptyString((uint8_t*)Blth_DataBuffer);
	Blth_DataIndex = 0;
	return E_OK;
}

Std_ReturnType Blth_sendCommand(uint8_t* CommandPtr)
{	
	/* Check if it is in Data Mode */
	if(Blth_CurrentState == BLTH_DATA_MODE)
	{   
		/*- Change to command mode -*/
		Blth_EnableCommandMode();
	}
	else
	{
		
	}
	Uart_sendPacket(CommandPtr, stringLength(CommandPtr)-1);	
	return E_OK;
}

Std_ReturnType Blth_getName(uint8_t *currentName)
{
	uint8_t commandFrame[11] = "AT+NAME?\r\n";
	uint8_t receivedFrame[25] = {0};
	uint8_t loopIndex=6, arrayIndex=0;
	
	Blth_sendCommand(commandFrame);
	
	Blth_readData(receivedFrame);
	
	if(receivedFrame[0] != '+')
	{
		return E_NOT_OK;
	}
	while(receivedFrame[loopIndex] != '\0')
	{
		currentName[arrayIndex++] = receivedFrame[loopIndex];
		loopIndex++;
	}
	currentName[arrayIndex-1] = '\0';
	
	return E_OK;
}

Std_ReturnType Blth_RenameDevice(uint8_t *newName)
{
	uint8_t commandFrame[50] = "AT+NAME=";
	
	stringConcatenate(commandFrame, newName);
	uint8_t frameLength = stringLength(commandFrame);
	commandFrame[frameLength-1] = '\r';
	commandFrame[frameLength] = '\n';
	commandFrame[frameLength+1] = '\0';
	Blth_sendCommand(commandFrame);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_getRole(uint8_t *currentRole)
{
	uint8_t commandFrame[11] = "AT+ROLE?\r\n";
	uint8_t receivedFrame[9] = {0};
	uint8_t roleIndex=6;
	
	Blth_sendCommand(commandFrame);
	
	Blth_readData(receivedFrame);
	
	if(receivedFrame[0] != '+')
	{
		return E_NOT_OK;
	}
	if(receivedFrame[roleIndex] == '0')
	{
		*currentRole = BLTH_ROLE_SLAVE;
	}
	else if(receivedFrame[roleIndex] == '1')
	{
		*currentRole = BLTH_ROLE_MASTER;
	}
	else
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_setSlave(void)
{
	uint8_t commandFrame[11] = "AT+ROLE=0\r\n";
	Blth_sendCommand(commandFrame);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_setMaster(void)
{
	uint8_t commandFrame[11] = "AT+ROLE=1\r\n";
	Blth_sendCommand(commandFrame);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_setRole(uint8_t Blth_Role)
{
	if(Blth_Role == BLTH_ROLE_MASTER)
	{
		Blth_setMaster();
	}
	else if(Blth_Role == BLTH_ROLE_SLAVE)
	{
		Blth_setSlave();
	}
	else
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
	commandFrame[frameLength+5] = '\0';
	Blth_sendCommand(commandFrame);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	return E_OK;
}

Std_ReturnType Blth_getBaudRate(uint32_t *currentBaudRate)
{
	uint8_t commandFrame[11] = "AT+UART?\r\n";
	uint8_t receivedFrame[22] = {0};
	uint8_t loopIndex=6;
	uint8_t stringBaudRate[8] = {0};
	
	Blth_sendCommand(commandFrame);
	
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

Std_ReturnType Blth_getOwnMacAddress(uint8_t *ownMacAddress)
{
	uint8_t commandFrame[10] = "AT+ADDR?\r\n";
	uint8_t receivedFrame[22] = {0};
	uint8_t loopIndex=6, arrayIndex=0;;
	
	Blth_sendCommand(commandFrame);
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

Std_ReturnType Blth_InquiryMode(uint8_t DeviceMacAddress[][17], uint8_t devicesNum, uint8_t timeOut)
{
	/*- Clear all paired devices -*/
	Blth_sendCommand((uint8_t*)"AT+RMAAD\r\n");
	/*- Check if command is acknowledged -*/
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	/*- Set Mode to any device -*/
	Blth_sendCommand((uint8_t*)"AT+CMODE=1\r\n");
	/*- Check if command is acknowledged -*/
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	/*- Initialize the device -*/
	Blth_sendCommand((uint8_t*)"AT+INIT\r\n");
	/*- Check if command is acknowledged -*/
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	uint8_t commandFrame[22] = "AT+INQM=1,";
	commandFrame[10] = devicesNum + '0';
	commandFrame[11] = ',';
	if(timeOut>=10)
	{
		commandFrame[12] = (uint8_t)(timeOut/10) + '0';
		commandFrame[13] = (uint8_t)(timeOut%10) + '0';
		commandFrame[14] = '\r';
		commandFrame[15] = '\n';
		commandFrame[16] = '\0';
	}
	else
	{
		commandFrame[12] = timeOut + '0';
		commandFrame[13] = '\r';
		commandFrame[14] = '\n';
		commandFrame[15] = '\0';
	}
	/*- Initialize the device -*/
	Blth_sendCommand(commandFrame);
	/*- Check if command is acknowledged -*/
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	/*- Start the Inquiry Mode -*/
	Blth_sendCommand((uint8_t*)"AT+INQ\r\n");
	/*- Wait for the data to be received -*/
	while(Blth_RX_Flag != DATA_RECEIVED);
	uint16_t bufferIndex = 0, macIndex=0, macCounter=0;
	while(Blth_DataBuffer[bufferIndex] != 'O')
	{
		if(Blth_DataBuffer[bufferIndex] == '+')
		{
			if(macCounter == devicesNum)
			{
				break;
			}
			bufferIndex += 5;
		}
		else if(Blth_DataBuffer[bufferIndex] == ',')
		{
			DeviceMacAddress[macCounter][macIndex] = '/';
			macIndex=0;
			macCounter++;
			while((Blth_DataBuffer[bufferIndex] != '+') && (Blth_DataBuffer[bufferIndex] != 'O'))
			{
				bufferIndex++;
			}
		}
		else
		{
			if(Blth_DataBuffer[bufferIndex] == ':')
			{
				DeviceMacAddress[macCounter][macIndex] = ',';
			}
			else
			{
				DeviceMacAddress[macCounter][macIndex] = Blth_DataBuffer[bufferIndex];
			}
			bufferIndex++;
			macIndex++;
		}
	}
	EmptyString((uint8_t*)Blth_DataBuffer);
	Blth_DataIndex=0;
	return E_OK;
}

Std_ReturnType Blth_LinkWithDevice(uint8_t *deviceMacAddress)
{
	uint8_t commandFrame[22] = "AT+LINK=";
	
	stringConcatenate(commandFrame,deviceMacAddress);
	uint8_t frameLength = stringLength(commandFrame);
	commandFrame[frameLength-1] = '\r';
	commandFrame[frameLength] = '\n';
	commandFrame[frameLength+1] = '\0';
	Blth_sendCommand(commandFrame);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_getPassword(uint8_t *currentPassword)
{
	uint8_t commandFrame[22] = "AT+PSWD?\r\n";
	uint8_t receivedFrame[25] = {0};
	uint8_t loopIndex=6, arrayIndex=0;
	
	Blth_sendCommand(commandFrame);
	
	Blth_readData(receivedFrame);
	
	if(receivedFrame[0] != '+')
	{
		return E_NOT_OK;
	}
	while(receivedFrame[loopIndex] != '\0')
	{
		currentPassword[arrayIndex++] = receivedFrame[loopIndex];
		loopIndex++;
	}
	currentPassword[arrayIndex-1] = '\0';
	
	return E_OK;
}

Std_ReturnType Blth_setPassword(uint8_t *newPassword)
{
	uint8_t commandFrame[22] = "AT+PSWD=\"";
	
	stringConcatenate(commandFrame, newPassword);
	uint8_t frameLength = stringLength(commandFrame);
	commandFrame[frameLength-1] = 0x22;
	commandFrame[frameLength] = '\r';
	commandFrame[frameLength+1] = '\n';
	commandFrame[frameLength+2] = '\0';
	Blth_sendCommand(commandFrame);
	
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

Std_ReturnType Blth_testDevice(void)
{
	uint8_t commandFrame[4] = "AT\r\n";
	Blth_sendCommand(commandFrame);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}

Std_ReturnType Blth_restoreDefault(void)
{
	uint8_t commandFrame[10] = "AT+ORGL\r\n";
	Blth_sendCommand(commandFrame);
	
	if(E_OK != Blth_checkOK())
	{
		return E_NOT_OK;
	}
	
	return E_OK;
}