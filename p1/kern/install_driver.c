/** @file install_driver.c
 *
 *  @brief Implementation of the handler_install function.
 *  Installs handlers for console, keyboard and timer
 *  interrupt handlers.
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug Not implemented
 */

#include <p1kern.h>
#include <stdio.h>
#include <simics.h>
#include <asm.h>
#include <keyhelp.h>
#include <seg.h>

#include "inc/keyboard_driver.h"

int handler_install(void (*tickback)(unsigned int)) {
	lprintf("Hello from handler_install function");

	//Get base address for IDT
	void *idt_base_addr = idt_base();
	lprintf("idt_base: %p", idt_base_addr);

	//Create an IDT entry for trap gate for keyboard driver
	void *idt_keyboard = ((char *)idt_base_addr)+(8*KEY_IDT_ENTRY);
	lprintf("idt_keyboard: %p", idt_keyboard);
	*((char *)idt_keyboard) &= 0xF8;
	*((char *)idt_keyboard+1) |= 0xF1;
	*(int *)((char *)idt_keyboard+2) = (int)getchar;
	*((char *)idt_keyboard+6) = SEGSEL_KERNEL_CS;

	lprintf("handler_install done");

	return 0;
}
