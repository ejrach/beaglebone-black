/*
 ============================================================================
 Name        : gpio_driver.h
 Author      : Eric
 Version     :
 Copyright   :
 Description : TBD
 ============================================================================
 */


#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include <stdint.h>

#define SOME_BYTES          100

/* This is the path corresponds to GPIOs in the 'sys' directory */
#define SYS_GPIO_PATH       "/sys/class/gpio"


#define HIGH_VALUE          1
#define LOW_VALUE           0

#define GPIO_DIR_OUT        HIGH_VALUE
#define GPIO_DIR_IN         LOW_VALUE

#define GPIO_LOW_VALUE      LOW_VALUE
#define GPIO_HIGH_VALUE     HIGH_VALUE

/* GPIO PIN DEFINITIONS */
/* Refer to the "Headerspinmap.xlsx file in my Dropbox for pin definitions */
// Pin Name					GPIO Number		Pin Header	Pin Number
#define GPIO_LED 			68				// P8		// 10



//public function prototypes .
int gpio_export(uint32_t gpio_num);
int gpio_configure_dir(uint32_t gpio_num, uint8_t dir_value);
int gpio_write_value(uint32_t gpio_num, uint8_t out_value);
int gpio_read_value(uint32_t gpio_num);
int gpio_configure_edge(uint32_t gpio_num, char *edge);
int gpio_file_open(uint32_t gpio_num);
int gpio_file_close(int fd);



#endif /* GPIO_DRIVER_H_ */
