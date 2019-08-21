/*
 ============================================================================
 Name        : mpu6050.h
 Author      : Eric
 Version     :
 Copyright   :
 Description : TBD
 ============================================================================
 */

#ifndef MPU6050_H_
#define MPU6050_H_


#include <stdint.h>


// MPU6050 Register Addresses (see "MPU-6000-Register-Map.pdf")
#define MPU6050_REG_POWER			0x6B	/* pg 8 */
#define WAKE_MODE					0x00	/* pg 40/41 */
// B2:0 -> CLKSEL 		-> 0 -> Use Internal 8MHz oscillator
// B3   -> TEMP_DIS 	-> 0 -> Enable temperature sensor
// B4 	-> don't care	-> 0
// B5	-> CYCLE		-> 0 -> With Sleep = 0, Disable Sleep inbetween data reads
// B6	-> SLEEP 		-> 0 ->	Take out of sleep mode
// B7   -> DEVICE_RESET -> 0 -> Don't reset to default values

// MPU6050 Register Addresses (see "MPU-6000-Register-Map.pdf")
#define MPU6050_REG_ACCEL_CONFIG	0x1C	/* pg 6 */
#define ACCEL_CONFIG				0x00	/* pg 15 */
// B2:0 -> don't care	-> 0
// B4:3 -> AFS_SEL 		-> 0 -> configure accelerometers to a full scale range of +/- 2g
// B5	-> ZA_ST		-> 0 -> Disable self test of Z-axis accelerometer
// B6	-> YA_ST 		-> 0 ->	Disable self test of Y-axis accelerometer
// B7   -> XA_ST		-> 0 -> Disable self test of X-axis accelerometer

// MPU6050 Register Addresses (see "MPU-6000-Register-Map.pdf")
#define MPU6050_REG_GYRO_CONFIG		0x1B	/* pg 6 */
#define GYRO_CONFIG					0x00	/* pg 14 */
// B2:0 -> don't care	-> 0
// B4:3 -> FS_SEL 		-> 0 -> configure gyros to a full scale range of +/- 250 deg/sec
// B5	-> ZG_ST		-> 0 -> Disable self test of Z-axis gyro
// B6	-> YG_ST 		-> 0 ->	Disable self test of Y-axis gyro
// B7   -> XG_ST		-> 0 -> Disable self test of X-axis gyro

// Accelerometer register addresses for data (see "MPU-6000-Register-Map.pdf")
#define MPU6050_REG_ACCEL_XOUT_H	0x3B	/* pg 7 */
#define MPU6050_REG_ACCEL_XOUT_L	0x3C	/* pg 7 */
#define MPU6050_REG_ACCEL_YOUT_H	0x3D	/* pg 7 */
#define MPU6050_REG_ACCEL_YOUT_L	0x3E	/* pg 7 */
#define MPU6050_REG_ACCEL_ZOUT_H	0x3F	/* pg 7 */
#define MPU6050_REG_ACCEL_ZOUT_L	0x40	/* pg 7 */

// Gyro register addresses for data (see "MPU-6000-Register-Map.pdf")
#define MPU6050_REG_GYRO_XOUT_H		0x43	/* pg 7 */
#define MPU6050_REG_GYRO_XOUT_L		0x44	/* pg 7 */
#define MPU6050_REG_GYRO_YOUT_H		0x45	/* pg 7 */
#define MPU6050_REG_GYRO_YOUT_L		0x46	/* pg 7 */
#define MPU6050_REG_GYRO_ZOUT_H		0x47	/* pg 7 */
#define MPU6050_REG_GYRO_ZOUT_L		0x48	/* pg 7 */

// Sensitivity scale factors accelerometer and gyro (see "MPU-6000-Datasheet.pdf)
#define ACCEL_FS_SENSITIVITY_0		16384	/* pg 13, tbl 6.2 */
#define ACCEL_FS_SENSITIVITY_1		8192	/* pg 13, tbl 6.2 */
#define ACCEL_FS_SENSITIVITY_2		4096	/* pg 13, tbl 6.2 */
#define ACCEL_FS_SENSITIVITY_3		2048	/* pg 13, tbl 6.2 */

#define GYRO_FS_SENSITIVITY_0		131		/* pg 12, tbl 6.1 */
#define GRYO_FS_SENSITIVITY_1		65.5	/* pg 12, tbl 6.1 */
#define GYRO_FS_SENSITIVITY_2		32.8	/* pg 12, tbl 6.1 */
#define GYRO_FS_SENSITIVITY_3		16.4	/* pg 12, tbl 6.1 */

// The I2C slave address of the MPU6050
#define MPU6050_SLAVE_ADDR			0x68

// The linux device file for the I2C-2 controller of the SOC
#define I2C_DEVICE_FILE				"/dev/i2c-2"

// ERROR CODES
#define SUCCESS						0
#define INIT_ERROR					-1
#define CONFIG_ERROR				-2
#define	WRITE_ERROR					-3
#define READ_ERROR					-4


// Function prototypes
void mpu6050_init(uint16_t fd);
int mpu6050_write(uint16_t fd, uint8_t addr, uint8_t data);
int mpu6050_read(uint16_t fd, uint8_t base_addr, char *pBuffer, uint32_t len);
void mpu6050_read_accel(uint16_t fd, short int *pBuffer);
void mpu6050_read_gyro(uint16_t fd, short int *pBuffer); //TBD - remove "int"?


#endif /* MPU6050_H_ */

