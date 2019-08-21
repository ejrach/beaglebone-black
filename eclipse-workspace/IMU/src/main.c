/*
 ============================================================================
 Name        : main.c
 Author      : Eric
 Version     :
 Copyright   :
 Description : TBD
 ============================================================================
 */

/*=================================================================
BBB_expansion_header_pins       GPIO number		Description
===================================================================
P8.10                            GPIO_68

P9.1                              ----            Ground
P9.7                              ----            +5V supply

Connections:
	TBD
=================================================================== */
 /*
 *
 *
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
 *		Give the project execute priveleges $ chmod +x IMU
 *		Run the project: $ ./IMU
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../Drivers/MPU6050/mpu6050.h"


int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
