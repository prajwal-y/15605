/** @file traceback_helper.h
 * 	@brief provides the definitions for the get_next_ret_addr and get_cur_ebp functions
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 */

#ifndef __TRACEBACK_HELPER_H
#define __TRACEBACK_HELPER_H

void *get_next_ret_addr(void *);
void *get_cur_ebp(void);
void *get_next_ebp(void *);

#endif
