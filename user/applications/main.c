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

#define WDT_KEEPALIVE
#define WDT_TIMEOUT 10
#define LED0_PIN    GET_PIN(B, 5)

int main(void)
{
    int count = 0;
    rt_uint32_t wdt_timeout = WDT_TIMEOUT;
    rt_device_t wdt_device = RT_NULL;
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED0_PIN, PIN_HIGH);
    wdt_device = rt_device_find("wdt");
    if(wdt_device == RT_NULL)
    {
        rt_kprintf("can't find the wdt device! \n");
        return -RT_ERROR;
    }
    rt_device_control(wdt_device, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, (void*)&wdt_timeout);
    rt_device_control(wdt_device, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    rt_kprintf("reduce the wdt timeout as [%02ds]\n",  WDT_TIMEOUT); 
    #ifdef WDT_KEEPALIVE
        rt_kprintf("refresh the wdt timeout.\n");
    #endif
    while (1)
     {
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_kprintf("Still living! (Time: %03ds)\n", count++);
        rt_thread_mdelay(1000);
        // rt_pin_write(LED0_PIN, PIN_LOW);
    #ifdef WDT_KEEPALIVE
        if(count % 9 == 0)
        {
            rt_device_control(wdt_device, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
            rt_kprintf("Feed Dog! (Time: %03ds)\n", count++);
        }
    #endif
     }
    // return RT_EOK;
}
