/*
 * UART_cfg.c

 *
 *  Created on: Aug 30, 2023
 *      Author: Sabry Elsayed
 */

#include "UART_cfg.h"

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "UART_int.h"

/*
 * BaudRate
 * Bluetooth    9600
 * WIFI         115200
 */
USART_InitType uart1_cfg =
{
		.BaudRate           = 115200,
		.DataWidth          = USART_MODE_8BIT,
		.StopBits           = USART_STOP_BIT_1,
		.Parity_Enable      = DISABLE,
		.Parity_Selection   = USART_EVEN_PARITY,
		.TransferDirection  = USART_TX_RX,
		.Oversampling       = USART_OVER_SAMPLING_8

};
 USART_InitType uart2_cfg =
{
		.BaudRate           = 9600,
		.DataWidth          = USART_MODE_8BIT,
		.StopBits           = USART_STOP_BIT_1,
		.Parity_Enable      = DISABLE,
		.Parity_Selection   = USART_EVEN_PARITY,
		.TransferDirection  = USART_TX_RX,
		.Oversampling       = USART_OVER_SAMPLING_8

};
USART_InitType uart6_cfg =
{
		.BaudRate           = 115200,
		.DataWidth          = USART_MODE_8BIT,
		.StopBits           = USART_STOP_BIT_1,
		.Parity_Enable      = DISABLE,
		.Parity_Selection   = USART_EVEN_PARITY,
		.TransferDirection  = USART_TX_RX,
		.Oversampling       = USART_OVER_SAMPLING_8

};


