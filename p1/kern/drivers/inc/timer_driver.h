/** @file timer_driver.h
 *
 *	@brief Interface for the timer handler
 *
 *	@author Prajwal Yadapadithaya (pyadapad)
 *	@bug None
 **/

#ifndef __timer_driver_h
#define __timer_driver_h

void timer_tick(void);

void initialize_callback(void *);

#endif
