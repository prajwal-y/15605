/** @file console_driver.c 
 *
 *  @brief Implementation of the console driver code.
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug First version implemented. Need to find bugs
 */

#include <p1kern.h>
#include <stdio.h>
#include <asm.h>
#include <stdint.h>

#define CONSOLE_SIZE (CONSOLE_WIDTH*CONSOLE_HEIGHT)
#define CURSOR_INVISIBLE ((CONSOLE_WIDTH*CONSOLE_HEIGHT)+1)

void set_hardware_cursor(int);
void scroll_console();
void set_char_at_pos(char, char, int);
void get_char_at_pos(char *, char *, int);

int cur_pos = 0; //Keeps track of the current position of the cursor
int cursor_visible = 1; //Boolean to keep track whether cursor is visible
char cur_color = FGND_WHITE; //Keeps track of the current color

int putbyte(char ch) {

	set_char_at_pos(ch, cur_color, cur_pos);

	cur_pos++;
	
	//If current position is beyond console size, scroll one row
	if(cur_pos == CONSOLE_SIZE) {
		scroll_console();
	}

	if(cursor_visible) {
		set_hardware_cursor(cur_pos);
	}
	return 0;

}

void putbytes(const char *s, int len) {
	int i;
	for(i = 0; i < len; i++) {
		putbyte(s[i]);
	}
}

int set_term_color(int color) {
	cur_color = (char)color;
	return 0;
}

void get_term_color(int *color) {
	*color = (int)cur_color;
}

int set_cursor(int row, int col) {
	int pos = row * CONSOLE_WIDTH + col;
	if(pos > CONSOLE_SIZE) {
		return -1;
	}
	cur_pos = pos;
	if(cursor_visible) {
		set_hardware_cursor(cur_pos);
	}
	return 0;
}

void get_cursor(int *row, int *col) {
	*row = cur_pos/CONSOLE_WIDTH;
	*col = cur_pos%CONSOLE_WIDTH;
}

void hide_cursor() {
	set_hardware_cursor(CURSOR_INVISIBLE);
	cursor_visible = 0;
}

void show_cursor() {
	cursor_visible = 1;
	set_hardware_cursor(cur_pos);
}

void clear_console() {
	int i, j;
	cur_pos = 0;
	for(i = 0; i < CONSOLE_HEIGHT; i++) {
		for(j = 0; j < CONSOLE_WIDTH; j++) {
			putbyte(' ');
		}
	}
	cur_pos = 0;
}

void draw_char(int row, int col, int ch, int color) {
	int pos = ((row*CONSOLE_WIDTH) + col);
	set_char_at_pos(ch, color, pos);
}

char get_char(int row, int col) {
	int pos = ((row*CONSOLE_WIDTH) + col);
	return *(char *)(CONSOLE_MEM_BASE + (2*pos));
}

/*
 * @brief Sets the hardware cursor to the specified position
 * @param position of the cursor
 * Eg: If cursor has to be places at (x, y), then the value
 * of position would be ((x*row)+y)
 * @return void
 */
void set_hardware_cursor(int position) {
	outb(CRTC_IDX_REG, CRTC_CURSOR_LSB_IDX);
	outb(CRTC_DATA_REG, (uint8_t)position);

	outb(CRTC_IDX_REG, CRTC_CURSOR_MSB_IDX);
	outb(CRTC_DATA_REG, (uint8_t)(position>>8));
}

/**
 * @brief Scrolls the console by 1 row
 *
 */
void scroll_console() {
	int i, j;
    for(i = 0; i < CONSOLE_HEIGHT-1; i++) {
        for(j = 0; j < CONSOLE_WIDTH; j++) {
			int new_pos = ((i+1)*CONSOLE_WIDTH + j);
			char ch, color;
			get_char_at_pos(&ch, &color, new_pos);
			
			int pos = ((i*CONSOLE_WIDTH) + j);
			set_char_at_pos(ch, color, pos);
        }
    }

	//Set the last row to empty
	for(j = 0; j < CONSOLE_WIDTH; j++) {
		int pos = ((CONSOLE_HEIGHT-1)*CONSOLE_WIDTH)+j;
		set_char_at_pos(' ', cur_color, pos);
	}

	//Set the cursor position appropriately
	cur_pos -= CONSOLE_WIDTH;
}

/**
 * @brief Sets the charatcer and the color at the specified
 * position.
 * @param ch Character to be set at the position
 * @param color Color of the character to be set
 * @param pos Position at which the character must be set
 * @return Void
 */
void set_char_at_pos(char ch, char color, int pos) {
	*(char *)(CONSOLE_MEM_BASE + (2*pos)) = ch;
	*(char *)(CONSOLE_MEM_BASE + (2*pos)+1) = cur_color;
}

/**
 * @brief Gets the character and the color at the specified
 * position
 */
void get_char_at_pos(char *ch, char *color, int pos) {
	*ch = *(char *)(CONSOLE_MEM_BASE + (2*pos));
	*color = *(char *)(CONSOLE_MEM_BASE + (2*pos+1));
}
