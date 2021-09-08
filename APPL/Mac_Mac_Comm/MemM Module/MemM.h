/*
 * MemM.h
 *
 * Created: 6/9/2021
 *  Author:Ahmed Nabil
 */ 


#ifndef MEMM_H_
#define MEMM_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "MemM_LCfg.h"
#include "Microcontroller/Std_types.h"
#include "Microcontroller/Platform_Types.h"
#include "Libraries/Utility Module/Utility.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS *-*-*-*-*-*/


/*- Primitive Types
-------------------------------*/
typedef uint8_t MemM_BlockID_t;
typedef uint8_t MemM_BlockPageNum_t;
typedef uint16_t MemM_BlockOffset_t;
typedef uint16_t MemM_BlockAddress_t;
typedef uint16_t MemM_BlockSize_t;
typedef uint8_t MemM_BlockData_t;


/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct  
{
	MemM_BlockID_t Block_ID;
	MemM_BlockAddress_t Address_Offset;
	MemM_BlockData_t Data[MEMM_MAX_DATA_SIZE];
	MemM_BlockSize_t Data_Size;
}MemM_BlockInfo_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Used to initialize the Memory Manager Module */
Std_ReturnType MemM_init(void);
/* Function to write the data of the Block in the memory */
Std_ReturnType MemM_writeBlock(MemM_BlockInfo_t *block_ptr);
/* Function to read data of a block from its location from the memory */
Std_ReturnType MemM_readBlock(MemM_BlockInfo_t *block_ptr);

Std_ReturnType MemM_eraseBlock(MemM_BlockID_t blockID);
Std_ReturnType MemM_createBlock(MemM_BlockInfo_t *block_ptr);
Std_ReturnType MemM_deleteBlock(MemM_BlockID_t blockID);
Std_ReturnType MemM_setBlock(MemM_BlockID_t blockID, MemM_BlockAddress_t MemoryAddress,
							 MemM_BlockData_t *dataPtr, MemM_BlockSize_t dataSize);

/* Configuration Extern Variable */

#endif /* MEMM_H_ */