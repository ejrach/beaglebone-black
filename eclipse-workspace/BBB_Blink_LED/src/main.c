/*
 * main.c
 *
 *  Created on: Aug 11, 2019
 *      Author: Eric
 *      Description:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>		//included for the signal interrupt handler
#include <unistd.h>


/*
 * This is the signal interrupt handler - looks for Cntrl-C to exit the program
 */
void sig_handler(int signo)
{
	if (signo == SIGINT)
		printf("\nreceived SIGINT\n");
	exit(1);
}


int main(void)
{
	int status;
	unsigned int cnt = 0;

	// Register the signal interrupt handler
	if (signal(SIGINT, sig_handler) == SIG_ERR )
	{
		printf("\ncan't catch SIG Handler\n");
		exit(1);
	}

	//First see if this file exists on the BBB HW.
	//You can manually browse the file system to determine this, or
	//do this programatically:
	status = access("/sys/class/gpio/gpio68/value", F_OK);

	if (status == -1)
	{
		//file doesn't exist
		printf("GPIO68 file doesn't exist. Execute \'echo $GPIO > export\' in  /sys/class/gpio at root where $GPIO = 68\n");
		exit(1);
	}

	//Set GPIO68 as output
	system("echo out > /sys/class/gpio/gpio68/direction");
	sleep(1);

	while(1)
	{
		if (cnt % 2 == 0)
		{
			printf("%u) LED --- ON\n", cnt);
			system("echo 1 > /sys/class/gpio/gpio68/value");
		}
		else
		{
			printf("%u) LED --- OFF\n", cnt);
			system("echo 0 > /sys/class/gpio/gpio68/value");
		}
		cnt += 1;
		sleep(1);
	}

	return 0;
}

