/*
 *    keyboard.c
 *    PS/2 keyboard driver using FIFO buffering
 * 
 *    2026/1/5 By GoutouStdio
 *    Based on Apache 2.0 open source license.
 *    Copyright © 2020 ViudiraTech, based on the Apache 2.0 license.
 */

#include <keyboard.h>
#include <ps2.h>
#include <interrupt.h>
#include <idt.h>
#include <printk.h>
#include <fifo.h>
#include <spin_lock.h>
#include <common.h>
#include <apic.h>
#include <string.h>

// 基础定义
static fifo_t kbd_fifo;                // 键盘FIFO缓冲区
static uint8_t kbd_buf[256];           // 键盘FIFO缓冲区存储
static volatile int shift_down = 0;    // Shift键按下状态
static volatile int caps_lock = 0;     // CapsLock 状态
static volatile int ctrl_down = 0;     // Ctrl键按下状态

/* 扫描码map1 */
static const char scancode_map[0x58] = {
    0,   0,  '1','2','3','4','5','6','7','8','9','0','-','=', '\b', '\t',
    'q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,  'a','s',
    'd','f','g','h','j','k','l',';','\'', '`', 0,  '\\','z','x','c','v',
    'b','n','m',',','.','/', 0,   '*', 0,  ' ', // 去0x39
};

/* keyboard 中断处理 */
INTERRUPT_BEGIN void keyboard_irq(interrupt_frame_t *frame)
{
    (void)frame;
    disable_intr();
    uint8_t sc = ps2_read_data();
    /* Shift 按下处理 */
    if (sc == 0x2A || sc == 0x36) { shift_down = 1; }
    else if (sc == 0xAA || sc == 0xB6) { shift_down = 0; }
    /* Ctrl 按下处理 (Left Ctrl是0x1D, break是0x9D) */
    if (sc == 0x1D) { ctrl_down = 1; }
    else if (sc == 0x9D) { ctrl_down = 0; }
    /* 大写锁定按下处理（代码 0x3A） */
    if (sc == 0x3A) { caps_lock = !caps_lock; }

    /* 如果加载完成，往FIFO放扫描码 */
    if (kbd_fifo.buffer && kbd_fifo.capacity) fifo_put(&kbd_fifo, sc);

    send_eoi();
    enable_intr();
}
INTERRUPT_END

/* 初始化ps2键盘驱动 */
void init_keyboard(void)
{
    /* 把缓冲区清0，保证万无一失 */
    memset(kbd_buf, 0, sizeof(kbd_buf));
    fifo_init(&kbd_fifo, kbd_buf, sizeof(kbd_buf));   // 初始化键盘fifo缓冲区
    register_interrupt_handler(IRQ_1, (void *)keyboard_irq, 0, 0x8e);  // 注册键盘中断
    plogk("keyboard: initialized!\n");
}

/* 获取一个键盘扫描码 */
int keyboard_get_scancode(uint8_t *sc)
{
    if (!sc) return -1;
    if (fifo_get(&kbd_fifo, sc) == 0) return 0;
    return -1;
}

/* 获取字符 */
int keyboard_getchar(char *out)
{
    uint8_t sc;
    if (keyboard_get_scancode(&sc) != 0) {
        return 0;
    }

    /* 忽略断开码（高位设置） */
    if (sc & 0x80) return 0;

    if (sc < sizeof(scancode_map) && scancode_map[sc]) {
        char c = scancode_map[sc];
        /* 处理大小写 */
        int make_upper = (caps_lock && (c >= 'a' && c <= 'z')) ? 1 : 0;
        if (shift_down) {
            if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
            else if (c == '1') c = '!';
            else if (c == '2') c = '@';
            else if (c == '3') c = '#';
            else if (c == '4') c = '$';
            else if (c == '5') c = '%';
            else if (c == '6') c = '^';
            else if (c == '7') c = '&';
            else if (c == '8') c = '*';
            else if (c == '9') c = '(';
            else if (c == '0') c = ')';
        }
        if (!shift_down && make_upper) c = c - 'a' + 'A';

        /* 如果 Ctrl 按下，把字母映射到控制字符（Ctrl+A=0x01 等） */
        if (ctrl_down) {
            if (c >= 'a' && c <= 'z') {
                c = (char)(c - 'a' + 1);
            } else if (c >= 'A' && c <= 'Z') {
                c = (char)(c - 'A' + 1);
            }
        }
        /* IME 已关闭；直接返回表 */
        *out = c;
        return 1;
    }
    return 0;
}
