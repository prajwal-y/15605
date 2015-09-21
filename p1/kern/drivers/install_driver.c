/** @file install_driver.c
 *
 *  @brief Implementation of the handler_install function.
 *  Installs handlers for console, keyboard and timer
 *  interrupt handlers.
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug None
 */

#include <p1kern.h>
#include <stdio.h>
#include <stdlib.h>
#include <simics.h>
#include <asm.h>
#include <keyhelp.h>
#include <seg.h>
#include <string.h>
#include <timer_defines.h>
#include <interrupt_defines.h>

#include "inc/handler_helper.h"
#include "inc/timer_driver.h"

/*IDT ENTRY CONSTANTS*/
#define HANDLER_OFFSET_1 16
#define SEGMENT_SELECTOR 16
#define RESERVED 5
#define ZEROES 3
#define SIZE 5
#define DPL 2
#define P 1
#define HANDLER_OFFSET_2 16

/*IDT ENTRY VALUES*/
#define RESERVED_VAL 0
#define ZEROES_VAL 0
#define SIZE_VAL 15
#define DPL_VAL 0
#define P_VAL 1

/*TIMER CONSTANTS*/
#define CPU_RATE 1193182
#define TIMER_PERIOD 100
#define LS_BYTE(x) ((x)&0xFF)
#define MS_BYTE(x) (((x)>>8)&0xFF)

/*OTHER CONSTANTS*/
#define IDT_ENRTY_LENGTH 8

/**
 * Data structure to pack the IDT entry.
 */
struct idt_entry {
	unsigned int handler_offset_1:HANDLER_OFFSET_1;
	unsigned int seg_selector:SEGMENT_SELECTOR;
	unsigned int reserved:RESERVED;
	unsigned int zeroes:ZEROES;
	unsigned int size:SIZE;
	unsigned int dpl:DPL;
	unsigned int p:P;
	unsigned int handler_offset_2:HANDLER_OFFSET_2;
};

/*Helper functions*/
static void populate_idt_entry(struct idt_entry *, void *);
static void initialize_timer_frequency(void);
static int add_idt_entry(int, void *);

/**
 * @brief Configures the keyboard and the timer handers
 * by adding an entry in the IDT.
 *
 * @param tickback Function pointer of the callback function
 * that needs to be called by the timer driver.
 *
 * @return 0 if interrupt handler installation is successful, 
 * -1 if not.
 */
int handler_install(void (*tickback)(unsigned int)) {

	int retval;

	/*Keyboard driver initialization*/
	retval = add_idt_entry(KEY_IDT_ENTRY, keyboard_handler);

	/*Timer driver initialization*/
	initialize_callback(tickback);	

	//Initialize timer frequency
	initialize_timer_frequency();

	//Create an IDT entry for timer driver
	retval = add_idt_entry(TIMER_IDT_ENTRY, timer_handler);

	return retval;
}

/**
 * @brief Initializes the timer frequency to generate interrupts
 * every 10 milliseconds
 * @return Void
 */
void initialize_timer_frequency() {
	outb(TIMER_MODE_IO_PORT, TIMER_SQUARE_WAVE);

	unsigned short rate = CPU_RATE/TIMER_PERIOD;

	outb(TIMER_PERIOD_IO_PORT, LS_BYTE(rate));
	outb(TIMER_PERIOD_IO_PORT, MS_BYTE(rate));
}

/**
 * @brief Function to add an entry to the IDT.
 *
 * @param entry_index Index of the IDT entry to be created
 * @param handler_addr Address of the handler
 *
 * @return 0 if successful, -1 if not.
 */
int add_idt_entry(int entry_index, void *handler_addr) {
	void *idt_base_addr = idt_base();
	void *idt_entry_addr = ((char *)idt_base_addr)+(IDT_ENRTY_LENGTH*entry_index);	

	struct idt_entry new_idt_entry;
	populate_idt_entry(&new_idt_entry, handler_addr);
	memcpy(idt_entry_addr, &new_idt_entry, sizeof(struct idt_entry));

	return 0; //TODO: FIX THIS
}

/**
 * @brief Function to populate the idt_entry struct with the given
 * interrupt handler
 *
 * @param idt_entry The entry which needs to be populated
 * @param handler_addr Address of the interrupt handler
 *
 * @return Void
 */
void populate_idt_entry(struct idt_entry *idt_entry, void *handler_addr) {
	idt_entry->handler_offset_1 = (int)handler_addr;
	idt_entry->seg_selector = SEGSEL_KERNEL_CS;
	idt_entry->reserved = RESERVED_VAL;
	idt_entry->zeroes = ZEROES_VAL;
	idt_entry->size = SIZE_VAL;
	idt_entry->dpl = DPL_VAL;
	idt_entry->p = P_VAL;
	idt_entry->handler_offset_2 = ((int)handler_addr>>16);
}
