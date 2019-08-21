/*
 ============================================================================
 Name        : mpu6050.c
 Author      : Eric
 Version     :
 Copyright   :
 Description : TBD
 ============================================================================
 */

/*
 * To include this driver in a project:
 * 		File -> Import -> General -> File System [Next]
 * 		Select the directory of where the drivers are.
 * 		Select Files
 * 		Click Advanced and ...
 * 			check "create link location" relative to PROJECT_LOC
 * 			check "create virtual folder"
 *
 * 		In the source file location of your main program include the header:
 * 			#include "../../Drivers/<FOLDERNAME>/<FILENAME>.h"
 */

#include <sys/fcntl.h>			//included for 'write'
#include <unistd.h>				//included for 'usleep'

#include "mpu6050.h"


// Initialize the MPU6050
// By default, the mpu6050 will be in sleep mode. So disable its sleep mode
// and configure the full scale ranges for the gyro and accelerometer.
void mpu6050_init(uint16_t fd)
{
	int ret;	//TBD: error catching

	// Disable the sleep mode - wake up the device and configure.
	ret = mpu6050_write(fd, MPU6050_REG_POWER, WAKE_MODE);
	usleep(500);

	// Adjust the full scale values for gyro and accelerometer
	ret = mpu6050_write(fd, MPU6050_REG_ACCEL_CONFIG, ACCEL_CONFIG);
	usleep(500);
	ret = mpu6050_write(fd, MPU6050_REG_GYRO_CONFIG, GYRO_CONFIG);
	usleep(500);
}

// Write 8 bit data to the sensor at the address indicated by address
int mpu6050_write(uint16_t fd, uint8_t addr, uint8_t data)
{
	int ret;
	char buf[2];

	buf[0] = addr;
	buf[1] = data;

	// The write function writes up to size bytes from buffer to the file with descriptor fd.
	// Always writing just 2 bytes.
	// The function returns the number of bytes actually written.
	ret = write(fd, buf, 2);

	if ( ret <= 0 )
	{
		perror("Write failed. Unable to write 2 bytes.\n");
		return WRITE_ERROR;
	}

	return SUCCESS;
}





