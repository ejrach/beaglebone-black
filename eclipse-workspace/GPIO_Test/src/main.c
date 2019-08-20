/*
 ============================================================================
 Name        : GPIO_Test.c
 Author      : Eric
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

/*
 * Instructions:
 *
 * Build Project
 * 		Project -> Build Project
 *
 * Transfer binaries from Eclipse to BBB
 * 		If "Remote Systems" is not visible, Open Remote Explorer:
 * 			Window -> Show View -> Other -> Remote Systems -> Remote Systems
 * 		Establish a connection to BBB by clicking the button in the Remote Systems view
 * 			Define a connection to a remote system -> SSH only
 * 			Follow the steps to connect to 192.168.7.2
 * 		Drag the binaries to the Desktop (or wherever you want to run it from)
 *
 * 	Open Putty to establish a SSH, login as debian
 *		Give the project execute priveleges $ chmod +x GPIO_Test
 *		Run the project: $ ./GPIO_Test
 *
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
	unsigned int cnt = 0;

	initialize_all_gpios();

	sleep(1);

	while(1)
	{
		if (cnt % 2 == 0)
		{
			printf("%u) LED --- ON\n", cnt);
			gpio_write_value(GPIO_LED, GPIO_HIGH_VALUE);
		}
		else
		{
			printf("%u) LED --- OFF\n", cnt);
			gpio_write_value(GPIO_LED, GPIO_LOW_VALUE);
		}
		cnt += 1;
		sleep(1);
	}


	return 0;
}
