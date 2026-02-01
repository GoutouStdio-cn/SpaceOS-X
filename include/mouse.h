/*
 *
 *      mouse.h
 *      鼠标驱动头文件
 *
 *      2026/2/1 By GoutouStdio
 *      Based on Apache 2.0 open source license.
 *      Copyright © 2020 ViudiraTech, based on the Apache 2.0 license.
 *
 */

#ifndef INCLUDE_MOUSE_H_
#define INCLUDE_MOUSE_H_

#include <stdint.h>

typedef struct {
    int8_t dx;
    int8_t dy;
    uint8_t buttons; /* bit0 左键, bit1 右键, bit2 中键 */
} mouse_event_t;

/* 初始化鼠标驱动 */
void init_mouse(void);

/* 获取鼠标事件 */
int mouse_get_event(mouse_event_t *ev);

#endif // INCLUDE_MOUSE_H_
