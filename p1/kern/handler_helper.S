/**
 * @file handler_helper.S
 * 
 * @brief asm implementation of the interrupt handlers for
 * keyboard and timer. Responsible for calling the C functions
 * of the respective drivers.
 *
 * Author: Prajwal Yadapadithaya (pyadapad)
 * @bug None
 */

.global timer_handler
.global keyboard_handler

timer_handler:
	PUSHA				/*Push all the registers on the stack*/
	CALL	timer_tick	/*Call the timer driver C function*/
	POPA				/*Restore all the registers from stack*/
	IRET				/*Return from interrupt handler*/

keyboard_handler:
	PUSHA							/*Push all the registers on the stack*/
	CALL	add_to_keyboard_buffer	/*Call the keyboard driver C function*/
	POPA							/*Restore all the registers from stack*/
	IRET							/*Return from interrupt handler*/
