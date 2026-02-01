/*
 *
 *      spaceos.h
 *      SpaceOS description header file
 *
 *      2026/2/1 By GoutouStdio
 *      Based on Apache 2.0 open source license.
 *      Copyright © 2020 ViudiraTech, based on the Apache 2.0 license.
 *
 */

#ifndef INCLUDE_SPACEOS_H_
#define INCLUDE_SPACEOS_H_

/* OS Name. */
#define OS_NAME "SpaceOS"

/* OS Version. */
#define OS_VERSION "6.0.260201"

/* OS Vendor. */
#define OS_VENDOR "GoutouStdio"

/* OS Develop stage.
 * 1: Alpha stage. more features, but have more bugs.
 * 2: Beta stage. base features complted, fix bugs.
 * 3. Stable stage. All features are fully developed, with virtually no bugs.
*/
#define OS_DEVELOP_STAGE 1

/* Developer Mode. */
#if OS_DEVELOP_STAGE == 2 || OS_DEVELOP_STAGE == 3
#   define DEBUG_MODE 0
#else
#   define DEBUG_MODE 1
#endif

/* Select whether to enable init process */
#define INIT_ENABLED 1

/* Get develop stage string. */
inline const char* get_develop_stage(void)
{
    switch (OS_DEVELOP_STAGE) // 第一次用case好吧
    {
        case 1:     return "alpha";
        case 2:     return "beta";
        case 3:     return "stable";
        default:    return "unknown";
    }
}

/* init process */
void init();

#endif // INCLUDE_SPACEOS_H_