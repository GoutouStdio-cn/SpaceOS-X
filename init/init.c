/*
 *
 *      init.c
 *      SpaceOS init process
 *
 *      2026/2/1 By GoutouStdio
 *      Based on Apache 2.0 open source license.
 *      Copyright © 2020 ViudiraTech, based on the Apache 2.0 license.
 *
 */

#include <spaceos.h>
#include <printk.h>
#include <debug.h>

/* init process */
void init(){
    // init begins
    // TODO: mount filesystems, start services, etc.
    plogk("init: SpaceOS Version %s (%s)\n", OS_VERSION, get_develop_stage());
    plogk("init: Starting init process...\n");

    panic("init: No init process implemented yet.\n");
}