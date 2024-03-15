/*
 * Bootloader_prv.h
 *
 *  Created on: Mar 15, 2024
 *      Author: sabry
 */

#ifndef APP_BOOTLOADER_BOOTLOADER_PRV_H_
#define APP_BOOTLOADER_BOOTLOADER_PRV_H_

typedef void (*function_t) (void);

function_t App_Call ;


#define APP_ADDRESS     0x08004000
#define RESRET_OFFSET   0x04


#define MAX_TIME_OUT    300000000
#define SCB_VTOR  *((volatile u32*)(0xE000ED00+0x08))
#define END_OF_FILE  '1'
#define OK           'k'

#endif /* APP_BOOTLOADER_BOOTLOADER_PRV_H_ */
