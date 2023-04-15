/*
 * @Author       : RoxyKko
 * @Date         : 2023-04-15 12:06:15
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-04-15 12:10:46
 * @Description  : 
 */

#include "spi.h"

// spi 初始化函数
int spi_init(spi_ctx_t *spi_ctx)
{
    int ret;

    spi_ctx->fd = open(spi_ctx->dev, O_RDWR);
    if(spi_ctx->fd < 0)
    {
        printf("open %s failed\n", spi_ctx->dev);
        return -1;
    }

    //设置spi接收和发送的模式
    ret = ioctl(spi_ctx->fd, SPI_IOC_WR_MODE, &spi_ctx->mode);
    if(ret < 0)
    {
        printf("ERROR: SPI set SPI_IOC_WR_MODE [0x%x] failure:%s\n", spi_ctx->mode, strerror(errno));
        close(spi_ctx->fd);
        return -1;
    }

    ret = ioctl(spi_ctx->fd, SPI_IOC_RD_MODE, &spi_ctx->mode);
    if(ret < 0)
    {
        printf("ERROR: SPI set SPI_IOC_RD_MODE [0x%x] failure:%s\n", spi_ctx->mode, strerror(errno));
        close(spi_ctx->fd);
        return -1;
    }

    //设置SPI通信接收和发送的字长
    ret = ioctl(spi_ctx->fd, SPI_IOC_WR_BITS_PER_WORD, &spi_ctx->bits);
    if(ret < 0)
    {
        printf("ERROR: SPI set SPI_IOC_WR_BITS_PER_WORD [0x%x] failure:%s\n", spi_ctx->bits, strerror(errno));
        close(spi_ctx->fd);
        return -1;
    }

    ret = ioctl(spi_ctx->fd, SPI_IOC_RD_BITS_PER_WORD, &spi_ctx->bits);
    if(ret < 0)
    {
        printf("ERROR: SPI set SPI_IOC_RD_BITS_PER_WORD [0x%x] failure:%s\n", spi_ctx->bits, strerror(errno));
        close(spi_ctx->fd);
        return -1;
    }

    //设置SPI通信的最大速率
    ret = ioctl(spi_ctx->fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_ctx->speed);
    if(ret < 0)
    {
        printf("ERROR: SPI set SPI_IOC_WR_MAX_SPEED_HZ [0x%x] failure:%s\n", spi_ctx->speed, strerror(errno));
        close(spi_ctx->fd);
        return -1;
    }

    printf("spi mode: ox%x\n", spi_ctx->mode);
    printf("bits per word: %d\n", spi_ctx->bits);
    printf("max speed: %d Hz (%d KHz)\n", spi_ctx->speed, spi_ctx->speed/1000);

    return spi_ctx->fd;
}


int transfer(spi_ctx_t *spi_ctx, uint8_t *tx, uint8_t *rx, size_t len)
{
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = len,
        .delay_usecs = spi_ctx->delay,
        .speed_hz = spi_ctx->speed,
        .bits_per_word = spi_ctx->bits,
    };

    // 发送并接收一组数据
    if(ioctl(spi_ctx->fd, SPI_IOC_MESSAGE(1), &tr) < 0)
    {
        printf("ERROR: SPI transfer failure:%s\n", strerror(errno));
        return -1;
    }
}