/*
 ============================================================================
 Name        : ConsoleTesting.c
 Author      : Eric
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>			//used for "system", "access"
#include <stdint.h>			//used for types

#define SYS_GPIO_PATH       "/sys/class/gpio"
#define SOME_BYTES			100



int main(void) {
	//puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

//	int len;
//	char buf[SOME_BYTES];
//
//	uint32_t gpio_num = 68;
//
//	//Need to form: "/sys/class/gpio/export"
//
//
//
//	len = snprintf(buf, sizeof(buf), "%d", gpio_num);
//
//	printf("gpio_num: %d\n", gpio_num);
//	printf("len: %d\n", len);
//	printf("buf: %s\n", buf);

	int i;
   char buf[12];

   for (i = 0; i < 100; i++) {
	  snprintf(buf, 12, "pre_%d_suff", i); // puts string into buffer
	  printf("%s\n", buf); // outputs so you can see it
   }



	return 0;
}
