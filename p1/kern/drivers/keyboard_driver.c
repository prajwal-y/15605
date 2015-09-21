/** @file keyboard_driver.c
 *
 *  @brief The keyboard device driver code. The keyboard driver
 *  stores the processed scancodes received in a queue implemented
 *  using a doubly linked list. When a readchar request comes, the
 *  head of the queue is removed until a valid character is obtained.
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug
 */

#include <p1kern.h>
#include <stdio.h>
#include <stdlib.h>
#include <simics.h>
#include <keyhelp.h>
#include <asm.h>
#include <interrupt_defines.h>

/**
 * Struct to store the keyboard buffer. The data structure used
 * is a queue implemented using a doubly linked list. Each time
 * a 
 */
typedef struct key {
	kh_type ch;
	struct key *next;
	struct key *prev;
}key;

key *head = NULL; /*Head of the queue*/
key *tail = NULL; /*Tail of the queue*/

/*Helper functions*/
static void add_key_to_queue(kh_type);
static int read_scancode();
static void notify_pic();

/**
 * @brief Function to get the first element in the queue
 * Removes the first element from the queue, and updates
 * the head of the queue.
 *
 * @return key First key in the queue. NULL if there are no
 * keys in the queue.
 */
key *dequeue() {
	if(head == NULL) {
		return NULL;
	}

	key *first = head;
	head = head->next;

	if(head != NULL) {
		head->prev = NULL;
	} else {
		tail = NULL;
	}

	first->next = NULL;
	return first;
}

/**
 * @brief Function to add a new key to the end of the queue.
 * Updates the end of the queue with the new key.
 *
 * @return Void
 */
void enqueue(key *key) {
	if(head == NULL) {
		head = key;
		tail = key;
		return;
	}
	tail->next = key;
	key->prev = tail;
	tail = key;
	tail->next = NULL;
}


/**
 * @brief Function to read and process a scancode
 * from keyboard
 *
 * @return Void
 *
 */
void add_to_keyboard_buffer() {
	int scancode = read_scancode();
	kh_type ch = process_scancode(scancode);
	add_key_to_queue(ch);
	notify_pic();
}

/**
 * @brief Reads a scancode from keyboard
 * 
 * @return int the value of the scancode
 */
int read_scancode() {
	return (int)inb(KEYBOARD_PORT);
}

/**
 * @brief Function to create an entry in the queue
 * and enqueue it, for a given character.
 *
 * @return Void
 */
void add_key_to_queue(kh_type ch) {
	key *entry = (key *)malloc(sizeof(key));
	entry->ch = ch;
	entry->next = NULL;
	entry->prev = NULL;
	enqueue(entry);
}

/**
 * @brief Function to notify the PIC that the scancode
 * has been processed.
 *
 * @return Void
 */
void notify_pic() {
	outb(INT_CTL_PORT, INT_ACK_CURRENT);
}

/**
 * @brief Function to return the next character in the keyboard
 * buffer. If there are no keys, the function does not block.
 *
 * @return int Next character in the keyboard buffer. If there
 * are no characters present, -1 is returned.
 */
int readchar() {
	key *first;
	while(((first=dequeue()) != NULL) && 
			((!KH_HASDATA(first->ch)) ||
			(KH_ISMAKE(first->ch)))) {
		free(first); /*We don't need this anymore*/
	}

	if(first != NULL) {
		char c = first->ch;
		free(first);
		return KH_GETCHAR(c);
	}

	return -1;
}
