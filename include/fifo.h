/*
 *
 *      fifo.h
 *      先进先出实现的头文件
 *
 *      2026/2/1 By GoutouStdio
 *      Based on Apache 2.0 open source license.
 *      Copyright © 2020 ViudiraTech, based on the Apache 2.0 license.
 *
 */

#ifndef INCLUDE_FIFO_H_
#define INCLUDE_FIFO_H_

#include <stdint.h>
#include <stddef.h>
#include <spin_lock.h>

typedef struct {
        uint8_t    *buffer;
        size_t      capacity;
        size_t      head;
        size_t      tail;
        spinlock_t  lock;
} fifo_t;

/* 初始化FIFO */
void fifo_init(fifo_t *f, uint8_t *buf, size_t capacity);

/* 往FIFO里放置数据 */
int fifo_put(fifo_t *f, uint8_t b);

/* 从FIFO里读数据 */
int fifo_get(fifo_t *f, uint8_t *b);

/* 检查空闲 */
int fifo_empty(fifo_t *f);

#endif // INCLUDE_FIFO_H_
