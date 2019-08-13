/*
 ============================================================================
 Name        : GPIO_Test.c
 Author      : Eric
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>		//included for the signal interrupt handler
#include <unistd.h>


#include "../drivers/gpio_driver.h"


/* This function initializes all the gpios for this application
 *  TODO : Error handling implementation
 */
int initialize_all_gpios(void)
{
	/* first lets export all the GPIOs */
	gpio_export(GPIO_LED);

	/*first configure the direction for GPIO pins */
    gpio_configure_dir(GPIO_LED, GPIO_DIR_OUT);

    return 0;
}



int main()
{
	initialize_all_gpios();

	gpio_write_value(GPIO_LED, GPIO_HIGH_VALUE);
	sleep(1);
	gpio_write_value(GPIO_LED, GPIO_LOW_VALUE);

	return 0;
}
