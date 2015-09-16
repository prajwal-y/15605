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
#include <string.h>
#include <timer_defines.h>
#include <interrupt_defines.h>

#include "inc/keyboard_driver.h"
#include "inc/timer_handler.h"

/**
 * Data structure to pack the IDT entry
 */
struct idt_entry {
	unsigned int handler_offset_1:16;
	unsigned int seg_selector:16;
	unsigned int reserved:8;
	unsigned int size:5;
	unsigned int DPL:2;
	unsigned int P:1;
	unsigned int handler_offset_2:16;
} keyboard_idt_entry, timer_idt_entry;

int handler_install(void (*tickback)(unsigned int)) {
	lprintf("Hello from handler_install function");

	//Get base address for IDT
	void *idt_base_addr = idt_base();
	lprintf("idt_base: %p", idt_base_addr);

	//Create an IDT entry for trap gate for keyboard driver
	/*void *idt_keyboard = ((char *)idt_base_addr)+(8*KEY_IDT_ENTRY);
	lprintf("idt_keyboard: %p handler_address: %p", idt_keyboard, getchar);
	keyboard_idt_entry.handler_offset_1 = (int)getchar;
	keyboard_idt_entry.seg_selector = SEGSEL_KERNEL_CS;
	keyboard_idt_entry.reserved = 0;
	keyboard_idt_entry.size = 15;
	keyboard_idt_entry.DPL = 0;
	keyboard_idt_entry.P = 1;
	keyboard_idt_entry.handler_offset_2 = ((int)getchar>>16);
	memcpy(idt_keyboard, &keyboard_idt_entry, sizeof(keyboard_idt_entry));*/


	//Initialize timer frequency
	outb(TIMER_MODE_IO_PORT, TIMER_SQUARE_WAVE);
	outb(TIMER_PERIOD_IO_PORT, 100);
	outb(TIMER_PERIOD_IO_PORT, 0);

	void *timer_handler_asm = timer_handler;

	//Repeat the same for timer handler	
	void *idt_timer = ((char *)idt_base_addr)+(8*TIMER_IDT_ENTRY);
	lprintf("idt_timer: %p handler_address: %p", idt_timer, timer_handler_asm);
	timer_idt_entry.handler_offset_1 = (int)timer_handler_asm;
	timer_idt_entry.seg_selector = SEGSEL_KERNEL_CS;
	timer_idt_entry.reserved = 0;
	timer_idt_entry.size = 15;
	timer_idt_entry.DPL = 0;
	timer_idt_entry.P = 1;
	timer_idt_entry.handler_offset_2 = ((int)timer_handler_asm>>16);
	memcpy(idt_timer, &timer_idt_entry, sizeof(timer_idt_entry));	

	return 0;
}
