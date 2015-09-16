/** @file timer_driver.c
 *
 *  @brief Code for timer device driver
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug Not implemented
 */

#include <p1kern.h>
#include <stdio.h>
#include <simics.h>
#include <asm.h>
#include <interrupt_defines.h>

void test_timer() {
	lprintf("In timer handler");
	outb(INT_CTL_PORT, INT_ACK_CURRENT);
}
