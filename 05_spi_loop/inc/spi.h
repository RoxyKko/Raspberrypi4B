/*** 
 * @Author       : RoxyKko
 * @Date         : 2023-04-15 12:04:52
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-04-15 12:41:13
 * @Description  : 
 */

#ifndef _SPI_H_
#define _SPI_H_

#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spi.h>
#include <linux/spi/spidev.h>


typedef struct spi_ctx_s{
    int         fd;
    char        dev[64];
    uint8_t     bits;
    uint16_t    delay;
    uint32_t    mode;
    uint32_t    speed;
} spi_ctx_t;

// spi 初始化
int spi_init(spi_ctx_t *spi_ctx);
// spi 传输
int transfer(spi_ctx_t *spi_ctx, uint8_t *tx, uint8_t *rx, size_t len);


#endif
