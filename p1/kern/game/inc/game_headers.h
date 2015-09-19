/** @file game_headers.h
 *  @brief All the header files required for various
 *  game files.
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug No known bugs
 */

#ifndef __game_headers_h
#define __game_headers_h

#include <p1kern.h>

/* libc includes. */
#include <stdio.h>
#include <simics.h>                 /* lprintf() */
#include <malloc.h>
#include <keyhelp.h>

/* multiboot header file */
#include <multiboot.h>              /* boot_info */

/* memory includes. */
#include <lmm.h>                    /* lmm_remove_free() */

/* x86 specific includes */
#include <x86/seg.h>                /* install_user_segs() */
#include <x86/interrupt_defines.h>  /* interrupt_setup() */
#include <x86/asm.h>                /* enable_interrupts() */

#include <string.h>

#endif
