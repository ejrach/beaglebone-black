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
//#include <stdlib.h>
#include <stdio.h>				//included for 'perror'

#include "mpu6050.h"


// Initialize the MPU6050
// By default, the mpu6050 will be in sleep mode. So disable its sleep mode
// and configure the full scale ranges for the gyro and accelerometer.
void mpu6050_init(uint16_t fd)
{
	// Disable the sleep mode - wake up the device and configure.
	mpu6050_write(fd, MPU6050_REG_POWER, WAKE_MODE);
	usleep(500);

	// Adjust the full scale values for gyro and accelerometer
	mpu6050_write(fd, MPU6050_REG_ACCEL_CONFIG, ACCEL_CONFIG);
	usleep(500);
	mpu6050_write(fd, MPU6050_REG_GYRO_CONFIG, GYRO_CONFIG);
	usleep(500);

	//return 0; //TBD return proper error
}

// Write 8 bit data to the sensor at the address indicated by address
int mpu6050_write(uint16_t fd, uint8_t addr, uint8_t data)
{
	int ret;
	char buf[2];

	buf[0] = addr;
	buf[1] = data;

	// Write the data to the device using the file descriptor handle.
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

// Read 'len' many bytes from the address of the sensor into the address indicated
// by pBuffer
int mpu6050_read(uint16_t fd, uint8_t base_addr, char *pBuffer, uint32_t len)
{
	int ret;
	char buf[2];

	buf[0] = base_addr;

	// Write the base address of the data that will be read using the file descriptor handle.
	// The write function writes up to size bytes from buffer to the file with descriptor fd.
	// Always writing just 1 byte.
	// The function returns the number of bytes actually written.
	ret = write(fd, buf, 1);
	if (ret <= 0)
	{
		perror("Write address failed.\n");
		return WRITE_ERROR;
	}

	// The read function reads up to size bytes from the file with descriptor fd,
	// storing the results in the buffer.
	// The function returns -1 if an error.
	ret = read(fd, pBuffer, len);
	if (ret <= 0)
	{
		perror("Read address failed.\n");
		return READ_ERROR;
	}

	return SUCCESS;
}

// Read accelerometer values of x, y, z into the buffer pBuffer
void mpu6050_read_accel(uint16_t fd, short int *pBuffer)
{
	//Each axis value is 2 bytes, so we need a buffer of 6 bytes
	char accel_buffer[6];

	//Start reading from the base address of accelerometer values
	//i.e. MPU6050_REG_ACCEL_XOUT_H
	mpu6050_read(fd, MPU6050_REG_ACCEL_XOUT_H, accel_buffer, 6);

	//pBuffer[0] = accelerometer x axis value
	//pBuffer[1] = accelerometer y axis value
	//pBuffer[2] = accelerometer z axis value
	pBuffer[0] = (int)( (accel_buffer[0] << 8 ) | accel_buffer[1] );
	pBuffer[1] = (int)( (accel_buffer[2] << 8 ) | accel_buffer[3] );
	pBuffer[2] = (int)( (accel_buffer[4] << 8 ) | accel_buffer[5] );
}

// Read gyro values of x, y, z into the buffer pBuffer
void mpu6050_read_gyro(uint16_t fd, short int *pBuffer)
{
	//Each axis value is 2 bytes, so we need a buffer of 6 bytes
	char gyro_buffer[6];

	//Start reading from the base address of gyro values
	//i.e. MPU6050_REG_GYRO_XOUT_H
	mpu6050_read(fd, MPU6050_REG_GYRO_XOUT_H, gyro_buffer, 6);

	//pBuffer[0] = gyro x axis value
	//pBuffer[1] = gyro y axis value
	//pBuffer[2] = gyro z axis value
	pBuffer[0] = (int)( (gyro_buffer[0] << 8 ) | gyro_buffer[1] );
	pBuffer[1] = (int)( (gyro_buffer[2] << 8 ) | gyro_buffer[3] );
	pBuffer[2] = (int)( (gyro_buffer[4] << 8 ) | gyro_buffer[5] );
}

