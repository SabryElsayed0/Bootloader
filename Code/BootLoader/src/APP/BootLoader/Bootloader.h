/*
 * Bootloader.h
 *
 *  Created on: Mar 15, 2024
 *      Author: sabry
 */

#ifndef APP_BOOTLOADER_BOOTLOADER_H_
#define APP_BOOTLOADER_BOOTLOADER_H_

void STK_CallBack(void);


void APP_vBootloaderInit(void);
void APP_vBootloaderStart(void);

#define Jump_To_APP     STK_CallBack

#endif /* APP_BOOTLOADER_BOOTLOADER_H_ */
