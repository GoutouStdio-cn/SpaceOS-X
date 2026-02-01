/*
 *
 *      keyboard.h
 *      键盘驱动头文件
 *
 *      2026/2/1 By GoutouStdio
 *      Based on Apache 2.0 open source license.
 *      Copyright © 2020 ViudiraTech, based on the Apache 2.0 license.
 *
 */

#ifndef INCLUDE_KEYBOARD_H_
#define INCLUDE_KEYBOARD_H_

#include <stdint.h>
#include <fifo.h>

/* 初始化键盘驱动 */
void init_keyboard(void);

/* 从键盘取一个字符 */
int keyboard_getchar(char *out);

/* 从键盘读扫描码 */
int keyboard_get_scancode(uint8_t *sc);

#endif // INCLUDE_KEYBOARD_H_
