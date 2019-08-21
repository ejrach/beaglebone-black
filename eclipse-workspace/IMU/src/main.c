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

#include "../../Drivers/MPU6050/mpu6050.h"

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <unistd.h>				//included for 'close'
#include <sys/ioctl.h>			//included for 'ioctl'
//#include <sys/stat.h>
//#include <sys/types.h>
#include <sys/fcntl.h>			//included for 'open'
#include <linux/i2c-dev.h>		//included for I2C_SLAVE definition
//#include <errno.h>








int main(void)
{
	// Define the file descriptor used by Linux OS
	int fd;
	int test = MAX_VALUE;

	// Define variables to hold the X, Y, Z raw values
	short int accel_value[3];
	short int gyro_value[3];

	// define variables to hold the accelerometer 'g' values
	double accel_x, accel_y, accel_z;

	// define variables to hold the gyro 'deg/sec' values
	double gyro_x, gyro_y, gyro_z;

	// First open the I2C device file to get a handle to the file descriptor, fd.
	// Exit program if failed.
	if (( fd = open(I2C_DEVICE_FILE, O_RDWR)) < 0 )
	{
		perror("Failed to open I2C device file.\n");
		return -1;
	}

	// Set the I2C slave address using ioctl I2C_SLAVE command.
	// Here we are specifying with what device address we want to communicate.
	// (ioctl performs general I/O control on file descriptors)
	// Exit program if failed. Close the file descriptor
	if ( ioctl(fd, I2C_SLAVE, MPU6050_SLAVE_ADDR) < 0 )
	{
		perror("Failed to set I2C slave address.\n");
		close(fd);
		return -1;
	}

	// Now initialize the MPU6050
	mpu6050_init(fd);
	mpu6050_write(fd, 0, 0);

	//
	//
	//
	//
	//


	return EXIT_SUCCESS;
}
