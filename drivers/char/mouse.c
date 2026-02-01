/*
 *
 *      mouse.c
 *      鼠标驱动
 *
 *      2026/2/1 By GoutouStdio
 *      Based on Apache 2.0 open source license.
 *      Copyright © 2020 ViudiraTech, based on the Apache 2.0 license.
 *
 */

#include <mouse.h>
#include <ps2.h>
#include <idt.h>
#include <printk.h>
#include <fifo.h>
#include <spin_lock.h>
#include <stdint.h>
#include <interrupt.h>
#include <common.h>
#include <apic.h>

/* 基本定义 */
static fifo_t mouse_fifo;        // 用于鼠标的 FIFO
static uint8_t mouse_buf[256];   // 鼠标缓冲区

/* 一些关于包的定义 */
static uint8_t pkt[3];
static int pkt_idx = 0;

/* 鼠标中断处理 */
INTERRUPT_BEGIN void mouse_irq(interrupt_frame_t *frame)
{
    (void)frame;    //我不想要警告
    disable_intr();
    uint8_t b = ps2_read_data();
    if (pkt_idx == 0) {
        if ((b & 0x08) == 0) {
            /* 丢包了，舍弃此字节 */
            /* 发送EOI信号，并重新开启中断 */
            send_eoi();
            enable_intr();
            return;
        }
        pkt[0] = b; pkt_idx = 1;
    } else {
        pkt[pkt_idx++] = b;
    }
    if (pkt_idx >= 3) {
        /* 往fifo放鼠标事件（dx, dy, buttons） */
        fifo_put(&mouse_fifo, pkt[0]);
        fifo_put(&mouse_fifo, pkt[1]);
        fifo_put(&mouse_fifo, pkt[2]);
        pkt_idx = 0;
    }
    send_eoi();
    enable_intr();
}

INTERRUPT_END

/* 初始化鼠标驱动 */
void init_mouse(void)
{
    /* 初始化鼠标的FIFO */
    fifo_init(&mouse_fifo, mouse_buf, sizeof(mouse_buf));
    /* 注册中断处理 */
    register_interrupt_handler(IRQ_12, (void *)mouse_irq, 0, 0x8e);
    plogk("mouse: IRQ handler registered.\n");

    /* 向设备2发送0xF4信号 */
    ps2_write_cmd(PS2_DEVICE_2);
    ps2_write_data(0xF4);
    /* 等待ACK响应0xFA */
    if (wait_ps2_read() == 0) {
        uint8_t ack = ps2_read_data();
        if (ack == PS2_RESPONSE_OK) plogk("mouse: enabled (ACK).\n");
        else plogk("mouse: enable returned %02x\n", ack);
    }
}

/* 获取鼠标事件 */
int mouse_get_event(mouse_event_t *ev)
{
    uint8_t b1, b2, b3;
    /* 从FIFO获取鼠标信息 */
    if (fifo_get(&mouse_fifo, &b1) != 0) return 0;
    if (fifo_get(&mouse_fifo, &b2) != 0) return 0;
    if (fifo_get(&mouse_fifo, &b3) != 0) return 0;

    /* 向提供的ev里写入事件 */
    ev->buttons = b1 & 0x07;
    ev->dx = (int8_t)b2;
    ev->dy = (int8_t)b3;
    return 1;
}
