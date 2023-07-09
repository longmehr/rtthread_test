/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-06     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include "board.h"
//官方示例代码开始
/*
 * 程序清单：这是一个 串口 设备使用例程
 * 例程导出了 uart_sample 命令到控制终端
 * 命令调用格式：uart_sample uart2
 * 命令解释：命令第二个参数是要使用的串口设备名称，为空则使用默认的串口设备
 * 程序功能：通过串口输出字符串"hello RT-Thread!"，然后错位输出输入的字符
*/

#include <rtthread.h>

#define SAMPLE_UART_NAME       "uart2"

static rt_device_t serial;
char str[] = "Hello RT-Thread!\r\n";
struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

int main(void)
{
    // config.baud_rate = BAUD_RATE_9600;
    serial = rt_device_find(SAMPLE_UART_NAME);
    rt_device_open(serial, RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, (void*)&config);
    while(1)
    {
        rt_device_write(serial, 0, str, (sizeof(str) - 1));
        rt_thread_mdelay(2000);
        rt_device_write(serial, 0, "ok\r\n", 8);
        rt_thread_mdelay(2000);
    }

    //return RT_EOK;
}
