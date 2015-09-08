/** @file traceback.c
 *  @brief The traceback function
 *
 *  This file contains the traceback function for the traceback library
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug Fix for alarming test remaining
 */

#include <signal.h>
#include <setjmp.h>
#include <sys/mman.h>
#include "traceback_internal.h"
#include "traceback_helper.h"
#include "traceback_print.h"

void *get_func_addr(void *);
void seg_fault_handler(int);
void config_signals();
struct sigaction restorehandler;
sigset_t *oldset;

/**
 *	@brief The main function of the traceback library that is
 *	responsible for printing the function name and its parameters.
 *	Also, configures the signal handlers required for traceback
 *	library.
 */
void traceback(FILE *fp)
{

	config_signals();

	//Get the current ebp
	void *reg_ebp = get_cur_ebp();

	while(1) {
		void *ret_addr = get_next_ret_addr(reg_ebp);
		void *func_addr = get_func_addr(ret_addr);
		reg_ebp = get_next_ebp(reg_ebp);
		if(print_func_name(func_addr, reg_ebp, fp)) {
			break;
		}
  }

	sigaction(SIGSEGV, &restorehandler, NULL);
	sigprocmask(SIG_SETMASK, oldset, NULL);
}

/**
 *	@brief Configure signals for the traceback function
 *	The mask of the calling thread is saved. A new mask
 *	is set for the traceback function, allowing only
 *	SIGSEGV while all other signals being deferred. The 
 *	signal handler for SIGSEGV is also set.
 */
void config_signals() {
	sigset_t newset;
  struct sigaction sig;
  
	sigprocmask(0, NULL, oldset);	//Get the old mask
  sigfillset(&newset);	//Block all signals
  sigdelset(&newset, SIGSEGV);	//Allow only SIGSEGV
  sigprocmask(SIG_SETMASK, &newset, NULL);	//Set the new mask
  
	sig.sa_handler = seg_fault_handler;	//Set the signal handler
  sigaction(SIGSEGV, &sig, &restorehandler);
}

/**
 *	@brief Given a return address, this function gets the 
 *				starting address of the function. If the starting
 *				address is not found on the function table, the 
 *				return address itself is returned.
 *
 * 	@param ret_addr Return address of the function
 *	@return Address of the function.
 */
void *get_func_addr(void *ret_addr) {
	int i=0;
	char *ptr = (char*)ret_addr;
	ptr = ptr - 1;
	while(!check_func_name(ptr) && i<MAX_FUNCTION_SIZE_BYTES) {
		ptr = ptr - 1;
		i++;
	}
	if(i==MAX_FUNCTION_SIZE_BYTES) {
		return ret_addr;
	}
	return ptr;
}

/**
 * @brief Signal handler for segmentation faults in traceback
 *	Segmentation faults can occur when the arguments are being
 *	parsed, and the arguments passsed are illegal pointers.
 */
void seg_fault_handler(int signum) {
	longjmp(env, 1);
}
