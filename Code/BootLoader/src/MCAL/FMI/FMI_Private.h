/*
 * FMI_Private.h
 *
 *  Created on: Sep 25, 2023
 *      Author: sabry
 */

#ifndef MCAL_FMI_FMI_PRIVATE_H_
#define MCAL_FMI_FMI_PRIVATE_H_



#define FLASH_BASE_ADDRESS   0x40023C00
typedef struct
{
	volatile u32  ACR;
	volatile u32  KEYR;
	volatile u32  OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 OPTCR ;
}FLASH_MemMap_t;

#define FLASH ((volatile FLASH_MemMap_t*)(FLASH_BASE_ADDRESS))

#define KEY1 0x45670123
#define KEY2 0xCDEF89AB
#define BSY  16
#define LOCK 31
#define SER  1
#define STRT 16
#define EOP  0
#define PG   0
#endif /* MCAL_FMI_FMI_PRIVATE_H_ */
