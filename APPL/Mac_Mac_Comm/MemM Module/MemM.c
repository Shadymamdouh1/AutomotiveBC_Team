/*
 * MemM.c
 *
 * Created: 6/9/2021
 *  Authors: Ahmed Nabil 
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "MemM.h"

/*- CONSTANTS
----------------------------------------------*/


/*- GLOBAL EXTERN VARIABLES -------------------------------------*/

MemM_BlockLocation_t MemM_BlocksAddresses[MEMM_MAX_BLOCKS_NUM];
uint8_t BlocksCounter=0;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: initialized BCM module.
************************************************************************************/
Std_ReturnType MemM_init(void)
{
	Eeprom_24_init();
	
	MemM_BlocksAddresses[0].Block_ID = 0;
	MemM_BlocksAddresses[0].Block_Address = 0x00;
	return E_OK;
}

/************************************************************************************
* Parameters (in): comChannelId
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: ask BCM to get any received data from a certain com. channel
************************************************************************************/

Std_ReturnType MemM_writeBlock(MemM_BlockInfo_t *block_ptr)
{
	if(EEPROM_24_STATUS_ERROR_NOK == Eeprom_24_writePacket(MemM_BlocksAddresses[block_ptr->Block_ID].Block_Address , block_ptr->Data, block_ptr->Data_Size))
	{
		return E_NOT_OK;
	}
	return E_OK;
}



/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state BCM Rx.
************************************************************************************/
Std_ReturnType MemM_readBlock(MemM_BlockInfo_t *block_ptr)
{
	if(EEPROM_24_STATUS_ERROR_NOK == Eeprom_24_readPacket(MemM_BlocksAddresses[block_ptr->Block_ID].Block_Address , block_ptr->Data, block_ptr->Data_Size))
	{
		return E_NOT_OK;
	}
	return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given device.
************************************************************************************/
Std_ReturnType MemM_eraseBlock(MemM_BlockID_t blockID)
{
	return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given device.
************************************************************************************/
Std_ReturnType MemM_createBlock(MemM_BlockInfo_t *block_ptr, uint8_t maxBlock_Size, MemM_BlockAddress_t Block_StartAddress)
{
	if((block_ptr == NULL_PTR) || (BlocksCounter == MEMM_MAX_BLOCKS_NUM-1) || (maxBlock_Size > MEMM_MAX_DATA_SIZE))
	{
		return E_NOT_OK;
	}
	
	block_ptr->Block_ID = BlocksCounter;
	block_ptr->Data_Size = maxBlock_Size;
	BlocksCounter++;
	MemM_BlocksAddresses[BlocksCounter].Block_Address = Block_StartAddress;
	MemM_BlocksAddresses[BlocksCounter].Block_ID = BlocksCounter;
	return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given device.
************************************************************************************/
Std_ReturnType MemM_deleteBlock(MemM_BlockID_t blockID)
{
	return E_OK;
}

/************************************************************************************
* Parameters (in): blockID - Index of the Block in the Array
*				   MemoryAddress - Address in the Memory.
*				   dataPtr - Pointer to the data to be saved.
*                  dataSize - Size of the data.
* Parameters (out): None
* Return value: Std_ReturnType
* Description: update the data of the block.
************************************************************************************/
#if 0
Std_ReturnType MemM_setBlock(MemM_BlockID_t blockID, MemM_BlockAddress_t MemoryAddress,
							 MemM_BlockData_t *dataPtr, MemM_BlockSize_t dataSize)
{
	if((blockID > MemM_BlocksCounter) || (dataPtr == NULL_PTR) || (dataSize > MEMM_MAX_DATA_SIZE))
	{
		return E_NOT_OK;
	}
	
	MemM_UserBlocks[blockID].Address_Offset = MemoryAddress;
	arrayCopy(dataPtr, MemM_UserBlocks[blockID].Data, dataSize);
	MemM_UserBlocks[blockID].Data_Size = dataSize;
	
	return E_OK;
}
#endif