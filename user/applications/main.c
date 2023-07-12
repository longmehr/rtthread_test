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
#include <rtdevice.h>
#include "board.h"
#include <watchdog.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define IWDG_DEVICE_NAME "wdt"
static rt_device_t wdg_dev;

static void idle_hook(void)
{
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
    rt_kprintf("feed the dog! \n");
}
int main(void)
{
    rt_err_t res = RT_EOK;
    rt_uint32_t timeout = 60;
    wdg_dev = rt_device_find(IWDG_DEVICE_NAME);
    if(!wdg_dev)
    {
        rt_kprintf("find %s failed! \n", IWDG_DEVICE_NAME);
        return -RT_ERROR;
    }
    res = rt_device_init(wdg_dev);
    if (res != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", IWDG_DEVICE_NAME);
        return -RT_ERROR;
    }
    res = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (res != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", IWDG_DEVICE_NAME);
        return -RT_ERROR;
    }
    rt_thread_idle_sethook(idle_hook);
    return res;
}
