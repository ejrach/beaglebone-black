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

#define MS_IN_ONE_SECOND		1000
#define MS_TO_SLEEP				250

void clear()
{
#if defined(__linux__) || defined(__unix__) || defined(__apple__)
	system("clear");
#endif
#if defined(__WIN32) || defined(_WIN64)
	system("cls");
#endif
}

int main(void)
{
	// Define the file descriptor used by Linux OS
	int fd;

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

	// Loop infinitely
	while(1)
	{
		// Clear the screen
		clear();

		mpu6050_read_accel(fd, accel_value);
		mpu6050_read_gyro(fd, gyro_value);

		// Convert accelerometer raw values read in, to 'g' values
		// Note: using ACCEL_FS_SENSITIVITY_0 because we have configured AFS_SEL to
		// full scale range +/- 2g
		accel_x = (double) accel_value[0] / ACCEL_FS_SENSITIVITY_0;
		accel_y = (double) accel_value[1] / ACCEL_FS_SENSITIVITY_0;
		accel_z = (double) accel_value[2] / ACCEL_FS_SENSITIVITY_0;

		// Convert gyro raw values read in, to 'deg/sec' values
		// Note: using GYRO_FS_SENSITIVITY_0 because we have configured FS_SEL to
		// full scale range of +/- 250 deg/sec
		gyro_x = (double) gyro_value[0] / GYRO_FS_SENSITIVITY_0;
		gyro_y = (double) gyro_value[1] / GYRO_FS_SENSITIVITY_0;
		gyro_z = (double) gyro_value[2] / GYRO_FS_SENSITIVITY_0;

		//Print the raw values read
		printf("Acc(raw)=> X:%d Y:%d Z:%d\n", accel_value[0], accel_value[1], accel_value[2]);
		printf("Gyro(raw)=> X:%d Y:%d Z:%d\n", gyro_value[0], gyro_value[1], gyro_value[2]);

		//Print the 'g' and 'deg/sec' values
		printf("accel_x = %0.2f   accel_y = %0.2f   accel_z = %0.2f\n", accel_x, accel_y, accel_z);
		printf("gyro_x  = %0.2f   gyro_y  = %0.2f   gyro_z  = %0.2f\n", gyro_x, gyro_y, gyro_z);

		//Wait for before looping again
		usleep( MS_TO_SLEEP * MS_IN_ONE_SECOND );



	}

	return EXIT_SUCCESS;
}
