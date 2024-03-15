#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "FMI_Private.h"
#include "FMI_Config.h"
#include "FMI_Interface.h"


void MFMI_vEraseSector(u8 Sector_Id)
{
	//wait bsy flag
	while(GET_BIT(FLASH->SR , 16) == 1);
	//unlock flash register
	if(GET_BIT(FLASH->CR , 31) == 1)
	{
		FLASH->KEYR = KEY1;
		FLASH->KEYR = KEY2;
	}
	//select sector
	FLASH->CR &=~((u32)(0b1111) << 3) ;
	FLASH->CR |=((Sector_Id) << 3);

	//activate sector
	SET_BIT(FLASH->CR , 1);

	//Start
	SET_BIT(FLASH->CR , 16);

	while(GET_BIT(FLASH->SR , 16) == 1);

	//clear flag
	SET_BIT(FLASH->SR , 0);

	CLR_BIT(FLASH->CR , 1);
}

void MEMI_vFlash(u32 Address , u16* pu16Data ,u32 u32NumOfElement)
{
	//wait bsy flag
	while(GET_BIT(FLASH->SR , 16));
	//unlock flash register
	if(GET_BIT(FLASH->CR , 31) == 1)
	{
		FLASH->KEYR = KEY1;
		FLASH->KEYR = KEY2;
	}

	//PSIZE
	FLASH->CR &=~((0b11) << 8);
	FLASH->CR |=((0b01) << 8);

	////activate Programming Flash
	SET_BIT(FLASH->CR , 0);

	for(u32 i = 0 ; i < u32NumOfElement ; i++)
	{
		*((volatile u16*)Address) =pu16Data[i];
		//(volatile u16*)Address++;
		Address+=2;
		//SET_BIT(FLASH->CR , 16);
		while(GET_BIT(FLASH->SR , 16) == 1);
		//clear flag
		SET_BIT(FLASH->SR , 0);
	}
	CLR_BIT(FLASH->CR , 0);

	//clear flag
	//SET_BIT(FLASH->SR , 0);
}
void MFMI_vEraseAppArea(void)
{
	for (u8 i = START_APP_SECTOR ; i <= END_APP_SECTOR ; i++)
	{
		MFMI_vEraseSector(i);
	}
}




