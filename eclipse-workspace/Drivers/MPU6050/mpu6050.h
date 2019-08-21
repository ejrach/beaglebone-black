/*
 ============================================================================
 Name        : mpu6050.h
 Author      : Eric
 Version     :
 Copyright   :
 Description : TBD
 ============================================================================
 */

// MPU6050 Register Addresses (see "MPU-6000-Register-Map.pdf")
#define MPU6050_REG_POWER			0x6B	/* pg 8 */
#define MPU6050_REG_ACCEL_CONFIG	0x1C	/* pg 6 */
#define MPU6050_REG_GYRO_CONFIG		0x1B	/* pg 6 */

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

#define MAX_VALUE					50

// The linux device file for the I2C-2 controller of the SOC
#define I2C_DEVICE_FILE				"/dev/i2c-2"

// Function prototypes




