/*
 * Bootloader_cfg.c

 *
 *  Created on: Mar 15, 2024
 *      Author: sabry
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/UART/UART_int.h"


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
			.Pin  = GPIO_PIN1 ,
			.Mode = GPIO_MODE_OUTPUT,
			.OutputSpeed = GPIO_OUTPUT_SPEED_MEDIUM,
			.OutputType = GPIO_OUTPUT_PUSH_PULL,
	};
