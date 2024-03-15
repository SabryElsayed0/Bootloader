
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/FMI/FMI_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/UART/UART_int.h"
#include "MCAL/UART/UART_prv.h"
#include "MCAL/STK/STK_int.h"
#include "APP/HexParser/HexParser_Interface.h"
extern USART_InitType uart2_cfg ;


u8 G_pu8RXBuffer[50];
u8 G_u8RXBufferCounter = 0;
u8 TimeOutFlag = 0;
u8 EraseFlag = 0;

typedef void (*function_t) (void);

function_t App_Call ;
#define SCB_VTOR  *((volatile u32*)(0xE000ED00+0x08))

void STK_CallBack( )
{
	 GPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN0 , GPIO_HIGH);

	TimeOutFlag = 1;
	SCB_VTOR = 0x08004000;
	App_Call = (function_t*) 0x08004004 ;
	App_Call();
}


//char record[] = ":108000003038580A00000000204C52203D20202551";
int main (void)
{
	RCC_voidInit();
	RCC_u8EnablePeripheralClock(RCC_APB1 ,RCC_EN_UART2 );
	RCC_u8EnablePeripheralClock(RCC_AHB1LP,RCC_EN_FMI);
	RCC_u8EnablePeripheralClock(RCC_AHB1 , RCC_AHB1_GPIOA);
	MSTK_vInit(); 	//HSI 16 MH / 8 = 2MH //TickTime = .5 us
	RCC_u8EnablePeripheralClock(RCC_APB2 , RCC_APB2_SYSCFG);

	GPIO_PinConfig uart_pinTx =
	{
			.Port = GPIO_PORTA,
			.Pin  = GPIO_PIN2 ,
			.Mode = GPIO_MODE_ALTERNATIVE,
			.OutputSpeed = GPIO_OUTPUT_SPEED_MEDIUM,
			.OutputType = GPIO_OUTPUT_PUSH_PULL,
			.alt_func = 7,
	};
	GPIO_PinConfig uart_pinRx =
	{
			.Port = GPIO_PORTA,
			.Pin  = GPIO_PIN3 ,
			.Mode = GPIO_MODE_ALTERNATIVE,
			.OutputSpeed = GPIO_OUTPUT_SPEED_MEDIUM,
			.PullState = GPIO_NO_PULL,
			//.OutputType = GPIO_OUTPUT_PUSH_PULL,
			.alt_func = 7,
	};
	GPIO_PinConfig Led =
	{
			.Port = GPIO_PORTA,
			.Pin  = GPIO_PIN0 ,
			.Mode = GPIO_MODE_OUTPUT,
			.OutputSpeed = GPIO_OUTPUT_SPEED_MEDIUM,
			.OutputType = GPIO_OUTPUT_PUSH_PULL,
	};
	GPIO_voidInit(&uart_pinTx);
	GPIO_voidInit(&uart_pinRx);
	GPIO_voidInit(&Led);
	///////////////////////////////////////////////////////////////////////
	/*5-MUSART Initialization*/
	uart2_cfg.BaudRate = 9600 ;
	MUSART_vInit(&uart2_cfg,USART2);
	/*6-Enable USARTx*/
	MUSART_vEnable(USART2);
	//////////////////////////////////////////////////////////////////////////

	//Enable Systick interupt //15 sec
	MSTK_vSetInterval_single(3000000 ,STK_CallBack );
	//	MGPIO_vSetAlternativeFunction(GPIO_PORTA , GPIO_PIN2 , 7);
	//		MGPIO_vSetAlternativeFunction(GPIO_PORTA , GPIO_PIN3 , 7);
	//	u16 data[3]={0x3044 , 0x3213};
	//	MFMI_vEraseSector(1);
	//	MEMI_vFlash(0x8008000 , record , 8);

	//
	//


	u8 L_u8UartRXStatus = 0;

	while(TimeOutFlag == 0)
	{

		L_u8UartRXStatus = MUSART_u8ReceiveByteAsynch_(USART2,&G_pu8RXBuffer[G_u8RXBufferCounter]);

		//G_pu8RXBuffer[G_u8RXBufferCounter] = MUSART_u8ReceiveByteSynchBlocking(USART2);

		if(L_u8UartRXStatus == 1)
		{
			/*Stop The time out*/
			 GPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN0 , GPIO_HIGH);

			if(EraseFlag == 0)
			{
				MSTK_vStopTimer();

				HexParser_vEraseAppArea();
				EraseFlag = 1;
			}

			if(G_pu8RXBuffer[G_u8RXBufferCounter] == '\n')
			{
				HexPasrser_vParseData(G_pu8RXBuffer);

				MUSART_vTransmitByteSynch(USART2,'k');
				G_u8RXBufferCounter = 0;

			}
			else
			{
				G_u8RXBufferCounter++;
			}
			//End of file
			if(G_pu8RXBuffer[8] == '1')
			{
				//MSTK_vSetInterval_single(1000000 ,STK_CallBack );
				STK_CallBack();

			}
			MUSART_vTransmitByteSynch(USART2,'k');

		}
	}
	return 0;

}






