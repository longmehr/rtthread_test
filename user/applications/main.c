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

#define IWDG_DEVICE_NAME    "wdt"    /* 看门狗设备名称 */
static rt_device_t wdg_dev;         /* 看门狗设备句柄 */
static void idle_hook(void)
{
    /* 在空闲线程的回调函数里喂狗 */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
    rt_kprintf("feed the dog!\n ");
}
static int iwdg_sample()
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 10;    /* 溢出时间 */
    char device_name[RT_NAME_MAX];
    /* 判断命令行参数是否给定了设备名称 */
    // if (argc == 2)
    // {
    //     rt_strncpy(device_name, argv[1], RT_NAME_MAX);
    // }
    // else
    // {
        rt_strncpy(device_name, IWDG_DEVICE_NAME, RT_NAME_MAX);
    // }
    /* 根据设备名称查找看门狗设备，获取设备句柄 */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return RT_ERROR;
    }
    /* 初始化设备 */
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", device_name);
        return RT_ERROR;
    }
    /* 设置看门狗溢出时间 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return RT_ERROR;
    }
    
    while (1)
    {
        idle_hook();
        rt_thread_mdelay(5000);
    }
		/* 设置空闲线程回调函数 */
    //rt_thread_idle_sethook(idle_hook);
    //return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(iwdg_sample, iwdg sample);


int main(void)
{
    int count = 1;
    while (count++)
     {
        rt_thread_mdelay(1000);
     }
    return RT_EOK;
}
