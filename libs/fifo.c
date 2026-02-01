/*
 *
 *      fifo.c
 *      先入先出实现
 *
 *      2026/2/1 By GoutouStdio
 *      Based on Apache 2.0 open source license.
 *      Copyright © 2020 ViudiraTech, based on the Apache 2.0 license.
 *
 */

#include <fifo.h>
#include <spin_lock.h>
#include <string.h>

/* 初始化FIFO */
void fifo_init(fifo_t *f, uint8_t *buf, size_t capacity)
{
    if (!f) return;
    memset(f, 0, sizeof(*f));
    f->buffer   = buf;
    f->capacity = capacity;
    f->head     = 0;
    f->tail     = 0;
    f->lock.lock = 0;
}

/* 往FIFO放置字节 */
int fifo_put(fifo_t *f, uint8_t b)
{
    int ret = -1;
    if (!f || !f->buffer || f->capacity == 0) return -1;
    uint64_t flags = spin_lock(&f->lock);
    size_t next = (f->head + 1) % f->capacity;
    if (next != f->tail) {
        f->buffer[f->head] = b;
        f->head = next;
        ret = 0;
    }
    spin_unlock(&f->lock, flags);
    return ret;
}

/* 从FIFO取字节 */
int fifo_get(fifo_t *f, uint8_t *b)
{
    int ret = -1;
    if (!f || !b || !f->buffer || f->capacity == 0) return -1;
    uint64_t flags = spin_lock(&f->lock);
    if (f->head != f->tail) {
        *b = f->buffer[f->tail];
        f->tail = (f->tail + 1) % f->capacity;
        ret = 0;
    }
    spin_unlock(&f->lock, flags);
    return ret;
}

/* 检查FIFO是否为空 */
int fifo_empty(fifo_t *f)
{
    int empty;
    uint64_t flags = spin_lock(&f->lock);
    empty = (f->head == f->tail);
    spin_unlock(&f->lock, flags);
    return empty;
}
