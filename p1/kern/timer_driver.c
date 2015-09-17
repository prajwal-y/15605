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

void (*callback_function) ();
unsigned int tickcount;

/**
 * @brief Function to initialize the callback function
 * to be called by the timer driver.
 *
 * @param func_addr Address of the function to be called
 * by the timer driver
 *
 * @return Void
 */
void initialize_callback(void *func_addr) {
	callback_function = func_addr;
	tickcount = 0;
}

/**
 * @brief Function which is called by the timer interrupt 
 * handler. This function is responsible for calling the 
 * callback function with the current count of timeticks.
 *
 * @return Void
 * @bug TODO: FIX TO RETURN IMMEDIATELY
 */
void timer_tick() {
	tickcount++;
	callback_function(tickcount);
	outb(INT_CTL_PORT, INT_ACK_CURRENT);
}
