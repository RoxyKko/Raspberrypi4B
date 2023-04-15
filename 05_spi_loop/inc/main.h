/*** 
 * @Author       : RoxyKko
 * @Date         : 2023-04-15 09:11:48
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-04-15 12:26:10
 * @Description  : 
 */
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/spi/spi.h>
#include <linux/spi/spidev.h>



#define PROG_VERSION "1.0.0"

#include "spi.h"

#endif // !_MAIN_H_