#include <rtthread.h>
#include <stdint.h>
#include <rtdevice.h>
#include <board.h>

/* ULOG_USING_SYSLOG */
#ifndef ULOG_USING_SYSLOG
#define LOG_TAG "bsp_i2c_tool"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>
#endif

int i2c_probe(struct rt_i2c_bus_device *bus, char addr)
{
    unsigned char cmd[1];
    cmd[0] = 0;

    struct rt_i2c_msg msgs;
    msgs.addr = addr;
    msgs.flags = RT_I2C_WR;
    msgs.buf = cmd;
    msgs.len = 0;

    return rt_i2c_transfer(bus, &msgs, 1);
}

void i2c_scan(int argc, char *argv[])
{
    // rt_kprintf("argc : %d,argv:[0]%s ,[1]%s\r\n", argc, argv[0], argv[1]);
    if (argc == 2)
    {
        rt_uint32_t start_addr = 0x00;
        rt_uint32_t stop_addr = 0x80;

        rt_uint8_t pos = start_addr <= 0xF ? 0x00 : start_addr & 0xF;
        struct rt_i2c_bus_device *dev;

        if (!strcmp(argv[1], "i2c1"))
        {
            rt_kputs("    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
            dev = (struct rt_i2c_bus_device *)rt_device_find(argv[1]);
            for (; pos < stop_addr; pos++)
            {
                if ((pos & 0xF) == 0)
                {
                    rt_kprintf("\n%02X: ", pos);
                }
                if (pos < start_addr)
                {
                    rt_kputs("   ");
                    continue;
                }
                if (i2c_probe(dev, pos) == 1)
                {
                    rt_kprintf("%02X", pos);
                }
                else
                {
                    rt_kputs("--");
                }
                rt_kputs(" ");
            }
            rt_kputs("\n");
        }
        else
        {
            rt_kprintf("please enter <dev_name>\r\n");
        }
    }
    else
    {
        rt_kprintf("Please enter a parameter\r\n");
    }
}

#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(i2c_scan, i2c_scan);
#endif
