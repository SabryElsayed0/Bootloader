
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "APP/BootLoader/Bootloader.h"

int main (void)
{

	/* Initialize Bootloader*/
    APP_vBootloaderInit();

    /* Start Bootloader*/
	APP_vBootloaderStart();
	while(1)
	{

	}
}





