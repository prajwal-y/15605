/** @file timer_driver.c
 *
 *  @brief Code for timer device driver. The timer driver
 *  keeps track of the tick count and each time a tick is 
 *  received, calls the callback function with the current
 *  tickcount
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug
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
 */
void timer_tick() {
	tickcount++;
	callback_function(tickcount);
	outb(INT_CTL_PORT, INT_ACK_CURRENT);
}
