/*
 * FMI_Interface.h
 *
 *  Created on: Sep 25, 2023
 *      Author: sabry
 */

#ifndef MCAL_FMI_FMI_INTERFACE_H_
#define MCAL_FMI_FMI_INTERFACE_H_



void MFMI_vEraseAppArea(void);
void MFMI_vEraseSector(u8 Sector_Id);
void MEMI_vFlash(u32 Address , u16* pu16Data ,u32 u32NumOfElement);


#endif /* MCAL_FMI_FMI_INTERFACE_H_ */
