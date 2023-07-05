/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

static struct rt_thread led_thread;
static rt_uint8_t rt_led_thread_stack[512];
static void led_thread_entry(void * para);
static rt_uint8_t led_thread_priority = 6;

#define LED0_PIN    GET_PIN(B, 5)
#define LED1_PIN    GET_PIN(E, 5)
/**
 *******************************************************************************
 ** \brief  Main function of template project
 **
 ** \param  None
 **
 ** \retval int32_t return value, if needed
 **
 ******************************************************************************/
int32_t main(void)
{
    rt_kprintf("hc32 example. \r\n");
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    	/* main thread */
	rt_thread_init(&led_thread,
					"led_thread",
					led_thread_entry,
					RT_NULL,
					&rt_led_thread_stack,
					sizeof(rt_led_thread_stack),
					led_thread_priority,
					1000);
	rt_thread_startup(&led_thread);
}


static void led_thread_entry(void * para)
{
    rt_kprintf("Entry %s. \r\n", __func__);
    while(1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_pin_write(LED1_PIN, PIN_HIGH);
		rt_thread_mdelay(1000);
        rt_pin_write(LED0_PIN, PIN_LOW);	
		rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}
