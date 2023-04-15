/*
 * @Author       : RoxyKko
 * @Date         : 2023-04-15 09:17:28
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-04-15 12:44:08
 * @Description  : spi回环测试
 */

#include "main.h"


// 打印程序帮助
static inline void print_usage(char *progname);

int main(int argc,char **argv)
{
    int             ret;
    spi_ctx_t       spi_ctx;
    char            *progname   = NULL;
    char            *spi_dev    = "/dev/spidev0.0";             //spi默认设备
    uint32_t        spi_speed   = 500000;                       //spi默认速度500k
    uint8_t         spi_mode    = SPI_MODE_2;                   //spi默认模式2
    uint8_t         spi_bits    = 8;                            //spi默认数据位8
    char            *tx         = "Hello Spi";                  //默认发送数据
    uint8_t         rx_buff[128];                               //接收缓存
    int             opt;

    struct option long_opting[] = {
        {"device", required_argument, NULL, 'd'},
        {"speed" , required_argument, NULL, 's'},
        {"print" , required_argument, NULL, 'p'},
        {"help"  , no_argument      , NULL, 'h'},
        {0       , 0                , 0   , 0  }
    };

    progname = (char *)basename(argv[0]);

    while((opt = getopt_long(argc, argv, "d:s:p:h", long_opting, NULL)) != -1)
    {
        switch(opt)
        {
            case 'd':
                spi_dev = optarg;
                break;
            case 's':
                spi_speed = atoi(optarg);
                break;
            case 'p':
                tx = optarg;
                break;
            case 'h':
                print_usage(progname);
                return 0;
        }
    }

    if(spi_speed == 0 || !tx)
    {
        print_usage(progname);
        return -1;
    }

    memset(&spi_ctx, 0, sizeof(spi_ctx_t));
    strcpy(spi_ctx.dev, spi_dev);

    spi_ctx.speed   = spi_speed;    //设置速率
    spi_ctx.mode    = spi_mode;     //设置spi模式
    spi_ctx.bits    = spi_bits;     //设置字长 8bit
    spi_ctx.delay   = 100;          //设置时延100us

    if(spi_init(&spi_ctx) < 0)
    {
        printf("spi_init() error\n");
        return -1;
    }
    printf("spi [dev %s] [fd = %d] init successfully\n", spi_ctx.dev, spi_ctx.fd);

    if(transfer(&spi_ctx, tx, rx_buff, strlen(tx)) < 0)
    {
        printf("transfer() error\n");
        return -1;
    }

    /*打印 tx_buffer 和 rx_buffer*/
    printf("tx_buffer: | %s |\n", tx);
    printf("rx_buffer: | %s |\n", rx_buff);

    return 0;
}

/**
 * @name: static inline void print_usage(char *progname)
 * @description: 打印帮助信息
 * @param {char} *progname 程序名称
 * @return {*}
 */
static inline void print_usage(char *progname)
{
    printf("Usage: %s [OPTION] ...\n", progname);
    printf("\nMandatory arguments to long options are mandatory for short option too:\n");

    printf(" -d[device ]: Setting device \n");
    printf(" -h[help   ]: Display this help information\n");
    printf(" -s[speed  ]: Setting spi speed\n");
    printf(" -p[print  ]: Setting tx space\n");


    printf("\nExample: %s -b -p 8900 -i 127.0.0.1\n", progname);
    return;
}



