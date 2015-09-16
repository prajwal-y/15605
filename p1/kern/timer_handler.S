/*
 * traceback_helper.S
 * Author: Prajwal Yadapadithaya (pyadapad)
 */

.global timer_handler

timer_handler:
	PUSHA
	CALL	test_timer	
	POPA
	IRET
