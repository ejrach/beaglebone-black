#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


#include "../drivers/gpio_driver.h"



/*
 *  GPIO export pin
 *
 */
int gpio_export(uint32_t gpio_num)
{
	int fd, len;
	char buf[SOME_BYTES];

	fd = open(SYS_GPIO_PATH "/export", O_WRONLY);
	if (fd < 0) {
		perror(" error opening export file\n");
		return fd;
	}

	//TBD: should I ignore exporting if exists? We don't need to export again if it does.
	//It seems to delete the directory when exported again
	//status = access("/sys/class/gpio/gpio68/value", F_OK);
	//THIS SEEMS TO WORK. REWRITE THIS CODE TO replace the access function
	//https://stackoverflow.com/questions/52125581/the-gpio-folder-is-deleted-when-the-same-gpio-is-exported-again
	int status = -1;
	status = access("/sys/class/gpio/gpio68/value", F_OK);
	if (status == -1)
	{
		len = snprintf(buf, sizeof(buf), "%d", gpio_num);
		write(fd, buf, len);
	}




	close(fd);

	return 0;
}

/*
 *  GPIO configure direction
 *  dir_value : 1 means 'out' , 0 means "in"
 */
int gpio_configure_dir(uint32_t gpio_num, uint8_t dir_value)
{
    int fd;	//file descriptor
    char buf[SOME_BYTES];

    snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/direction", gpio_num);

    //debug
    printf("gpio_num: %d\n", gpio_num);
    printf("dir_value: %d\n", dir_value);
    printf("buf: %s\n", buf);

    system("echo out > /sys/class/gpio/gpio68/direction");


//    fd = open(buf, O_WRONLY);
//
//    printf("fd: %d\n", fd);
//
//    if (fd < 0) {
//        perror("gpio direction configure\n");
//        return fd;
//    }
//
//    if (dir_value)
//        write(fd, "out", 4); //3+1  +1 for NULL character
//    else
//        write(fd, "in", 3);

//    close(fd);
    return 0;
}

/*
 *  GPIO write value
 *  out_value : can be either 0 or 1
 */
int gpio_write_value(uint32_t gpio_num, uint8_t out_value)
{
    int fd;
    char buf[SOME_BYTES];

    snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/value", gpio_num);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio write value\n");
        return fd;
    }

    if (out_value)
        write(fd, "1", 2);
    else
        write(fd, "0", 2);

    close(fd);
    return 0;
}

/*
 *  GPIO read value
 */
int gpio_read_value(uint32_t gpio_num)
{
    int fd;
    uint8_t read_value=0;
    char buf[SOME_BYTES];

    snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/value", gpio_num);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio read value\n");
        return fd;
    }

    read(fd, &read_value, 1);

    close(fd);
    return read_value;
}


/*
 *  GPIO configure the edge of trigger
 *  edge : rising, falling
 */
int gpio_configure_edge(uint32_t gpio_num, char *edge)
{
    int fd;
    char buf[SOME_BYTES];

    snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/edge", gpio_num);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio configure edge\n");
        return fd;
    }

    write(fd, edge, strlen(edge) + 1);
    close(fd);
    return 0;
}

/*
 *  Open the sys fs file corresponding to gpio number
 */
int gpio_file_open(uint32_t gpio_num)
{
    int fd;
    char buf[SOME_BYTES];

    snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/value", gpio_num);

    fd = open(buf, O_RDONLY | O_NONBLOCK );
    if (fd < 0) {
        perror("gpio file open\n");
    }
    return fd;
}

/*
 *  close a file
 */
int gpio_file_close(int fd)
{
    return close(fd);
}
