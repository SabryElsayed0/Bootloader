/*
 * Bootloader.c
 *
 *  Created on: Mar 15, 2024
 *      Author: sabry
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/FMI/FMI_Interface.h"
#include "../../MCAL/UART/UART_int.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/STK/STK_int.h"
#include "../HexParser/HexParser_Interface.h"
#include "Bootloader_cfg.h"
#include "Bootloader_prv.h"
#include "Bootloader.h"



/* Buffer To receive hex file records */
static u8 G_pu8RXBuffer[50];

/* Buffer Counter  */
static u8 G_u8RXBufferCounter = 0;

/* To indicate End of bootloader processing  */
static u8 TimeOutFlag = 0;




void STK_CallBack( )
{

	TimeOutFlag = 1;
	SCB_VTOR = APP_ADDRESS ;
	App_Call = *(function_t*) (APP_ADDRESS + RESRET_OFFSET);
	App_Call();

}


static void APP_vBootloaderEraseAppArea(void)
{
	static u8 first_call = FALSE ;

	if(first_call == FALSE)
	{
		/*Stop Timer Because Application code in processing*/
		MSTK_vStopTimer();
		HexParser_vEraseAppArea();
		first_call = TRUE ;
	}

}


void APP_vBootloaderInit()
{
	/* Initialize RCC */
	RCC_voidInit();

	/* Enable Clock to UART , Flash Driver , and GPIOA  */
	RCC_u8EnablePeripheralClock(RCC_APB1 ,RCC_EN_UART2 );
	RCC_u8EnablePeripheralClock(RCC_AHB1LP,RCC_EN_FMI);
	RCC_u8EnablePeripheralClock(RCC_AHB1 , RCC_AHB1_GPIOA);
	RCC_u8EnablePeripheralClock(RCC_APB2 , RCC_APB2_SYSCFG);

	/* Initialize System Timer */
	MSTK_vInit(); 	//HSI 16 MH / 8 = 2MH //TickTime = .5 us


	/* Inialize UART Pins */
	GPIO_voidInit((GPIO_PinConfig*)&uart_pinTx);
	GPIO_voidInit((GPIO_PinConfig*)&uart_pinRx);
	GPIO_voidInit((GPIO_PinConfig*)&Led);

	/*5-MUSART Initialization*/
	MUSART_vInit(&uart2_cfg,USART2);
	/*6-Enable USARTx*/
	MUSART_vEnable(USART2);

	//Enable Systick interupt //15 sec
	MSTK_vSetInterval_single(MAX_TIME_OUT ,Jump_To_APP );

}
void APP_vBootloaderStart(void)
{
	u8 L_u8UartRXStatus = FALSE ;
	u8 L_u8AreaErased   = FALSE ;
	while(TimeOutFlag == FALSE)
	{

		/*Read the data from UART2*/
		L_u8UartRXStatus = MUSART_u8ReceiveByteAsynch_(USART2,&G_pu8RXBuffer[G_u8RXBufferCounter]);

		if(L_u8UartRXStatus == TRUE)
		{
			/*Erase App Area */
			if(L_u8AreaErased == FALSE)
			{
				APP_vBootloaderEraseAppArea();
				L_u8AreaErased = TRUE ;
			}else{}

			/* To indicate foe reception complete  record */
			if(G_pu8RXBuffer[G_u8RXBufferCounter] == '\n')
			{
				/*Parse the Record and write it on the flash*/
				HexPasrser_vParseData(G_pu8RXBuffer);

				/* To synchronization with python script to send another record */
				MUSART_vTransmitByteSynch(USART2,OK);
				G_u8RXBufferCounter = 0;

			}
			else
			{
				G_u8RXBufferCounter++;
			}
			//End of file
			if(G_pu8RXBuffer[8] == END_OF_FILE)
			{
				Jump_To_APP();
			}

		}
	}

}



