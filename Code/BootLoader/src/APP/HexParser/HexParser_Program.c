
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/FMI/FMI_Interface.h"
#include "HexParser_Interface.h"

#define  FLASH_BASE_ADDR       0x8000000

u16 Buffer[100];
static  u8 HexParser_u8AsciiHex (u8 Copy_u8Ascii )
{
	u8 Local_u8HexValue = 0;

	if(Copy_u8Ascii >= '0' && Copy_u8Ascii <= '9')
	{
		Local_u8HexValue = Copy_u8Ascii - '0';
	}
	else if(Copy_u8Ascii >= 'A' && Copy_u8Ascii <= 'F')
	{
		//		Local_u8HexValue = (Copy_u8Ascii - 'A') + 10;
		Local_u8HexValue = Copy_u8Ascii - 55;

	}

	return Local_u8HexValue;
}


void HexPasrser_vParseData ( u8  Copy_pu8Data[] )
{
	//Character count variables
	u8 CC_Low  = 0 ;
	u8 CC_High   = 0 ;
	u8 CC      = 0 ;

	//4 Digits for conversion
	//Because of half Word (16 bit)
	u8 Digit0 = 0;
	u8 Digit1 = 0;
	u8 Digit2 = 0;
	u8 Digit3 = 0;

	//Address Variable
	u32 Address  = 0;
	if(Buffer[8] == '4')
	{}
	else
	{
		//1- Convert Character Count
		CC_High = HexParser_u8AsciiHex(Copy_pu8Data[1]);
		CC_Low  = HexParser_u8AsciiHex(Copy_pu8Data[2]);
		CC      = (CC_High << 4) | CC_Low ;

		//2-Convert Address
		Digit0 = HexParser_u8AsciiHex(Copy_pu8Data[3]);
		Digit1 = HexParser_u8AsciiHex(Copy_pu8Data[4]);
		Digit2 = HexParser_u8AsciiHex(Copy_pu8Data[5]);
		Digit3 = HexParser_u8AsciiHex(Copy_pu8Data[6]);
		Address = (FLASH_BASE_ADDR) |
				(Digit0 << 12)    |
				(Digit1 << 8)     |
				(Digit2 << 4)     |
				(Digit3 << 0 );

		for(s8 i = 0 ; i < (CC / 2) ; i++)
		{
			Digit0 = HexParser_u8AsciiHex(Copy_pu8Data[(4 * i) + 9]);
			Digit1 = HexParser_u8AsciiHex(Copy_pu8Data[(4 * i) + 10]);
			Digit2 = HexParser_u8AsciiHex(Copy_pu8Data[(4 * i) + 11]);
			Digit3 = HexParser_u8AsciiHex(Copy_pu8Data[(4 * i) + 12]);
			Buffer[i] = (Digit0 << 12)    |
					(Digit1 << 8)     |
					(Digit2 << 4)     |
					(Digit3 << 0 );
			//			 L_u16DataOfRecord[L_u8Counter]= (digit0<<12) |(digit1<<8)|(digit2<<4)|(digit3);
				Buffer[i]= (Digit2<<12) |(Digit3<<8)|(Digit0<<4)|(Digit1);

		}

		MEMI_vFlash(Address ,Buffer ,(CC / 2)  );
	}
}
void HexParser_vEraseAppArea(void)
{
	MFMI_vEraseAppArea();
}







