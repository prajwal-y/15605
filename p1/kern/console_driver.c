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
#include <string.h>

#define CONSOLE_SIZE (CONSOLE_WIDTH*CONSOLE_HEIGHT)
#define CURSOR_INVISIBLE ((CONSOLE_WIDTH*CONSOLE_HEIGHT)+1)

static void set_hardware_cursor(int);
static void scroll_console();
static void set_char_at_pos(char, char, int);
//static void get_char_at_pos(char *, char *, int);

int cur_pos = 0; //Keeps track of the current position of the cursor
int cursor_visible = 1; //Boolean to keep track whether cursor is visible
char cur_color = FGND_WHITE; //Keeps track of the current color


/**
 * @brief Puts a character in the current position of the cursor, and 
 * increments the cursor position by 1. In case the current position of
 * the cursor goes beyond the last possible valid value (depending on
 * the size of the console), the console is scrolled by one row.
 *
 * Special characters such as '\n', '\r' and '\b' are handled separately.
 *
 * @param ch The character to be printed in the console at the current
 * position
 *
 * @return the input character
 *
 */
int putbyte(char ch) {

	switch(ch) {
		case '\n':
			cur_pos += CONSOLE_WIDTH - (cur_pos%CONSOLE_WIDTH);
			break;
		case '\r':
			cur_pos -= cur_pos%CONSOLE_WIDTH;
			break;
		case '\b':
			cur_pos?:cur_pos--;
			set_char_at_pos(' ', cur_color, cur_pos);
			break;
		default:
			set_char_at_pos(ch, cur_color, cur_pos);
			cur_pos++;
			break;
	}
	
	//If current position is beyond console size, scroll one row
	if(cur_pos == CONSOLE_SIZE) {
		scroll_console();
	}

	if(cursor_visible) {
		set_hardware_cursor(cur_pos);
	}

	return 0;

}

/**
 * @brief Prints a character string of a given length at the current
 * position of the cursor. The position of the cursor is incremented
 * by the length of the string to be printed. If the string is longer
 * than the current line, the string is continued to be printed in the
 * next line. If the string exceeds the available space in the console,
 * the console is scrolled up by one row, and the string will be printed.
 *
 * @param s The string to be printed
 * @param len Length of the string to be printed
 *
 * @return Void
 */
void putbytes(const char *s, int len) {
	int i;
	for(i = 0; i < len; i++) {
		putbyte(s[i]);
	}
}

/**
 * @brief Sets the foreground and background colors of the future
 * characters to be printed in the console.
 *
 * @param color The new color that needs to be set
 *
 * @bug need to check if color is valid
 *
 * @return 0 is successful, -1 if the color code is invalid
 */
int set_term_color(int color) {
	cur_color = (char)color;
	return 0;
}

/**
 * @brief Gets the current foreground and background color
 * of the characters on the console
 *
 * @param color The address to which the current color
 * will be written
 *
 * @return Void
 */
void get_term_color(int *color) {
	*color = (int)cur_color;
}

/**
 * @brief Sets the logical cursor to the position defined
 * by row and column. Subsequent prints will be continued
 * from the new position of the cursor.
 *
 * @param row The new row of the cursor
 * @param col The new column of the cursor
 *
 * @return 0 if successful, -1 if the new position is invalid
 */
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

/**
 * @brief Gets the current position of the logical
 * cursor
 *
 * @param row The address where the row value needs to be set
 * @param col The address where the column value needs to be set
 *
 * @return Void
 */
void get_cursor(int *row, int *col) {
	*row = cur_pos/CONSOLE_WIDTH;
	*col = cur_pos%CONSOLE_WIDTH;
}

/**
 * @brief Hides the cursor. Cursor will not be shown
 * until show_cursor() is called.
 *
 * @return Void
 */
void hide_cursor() {
	set_hardware_cursor(CURSOR_INVISIBLE);
	cursor_visible = 0;
}

/**
 * @brief Shows the cursor. If cursor is already shown,
 * this will have no effect.
 *
 * @return void
 */
void show_cursor() {
	if(cursor_visible) {
		return;
	}
	cursor_visible=1;
	set_hardware_cursor(cur_pos);
}

/**
 * @brief Clears the entire console. The cursor is reset
 * to the first row and first column
 *
 * @return Void
 */
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

/**
 * @brief Prints a given character at given row and
 * column using the given color.
 *
 * @param row Row at which character needs to be printed
 * @param col Column at which character needs to be printed
 * @param ch Character to be printed
 * @param color Color of the character to be printed
 *
 * @bug If any argument is invalid, the function should
 * do nothing
 *
 * @return Void
 */
void draw_char(int row, int col, int ch, int color) {
	int pos = ((row*CONSOLE_WIDTH) + col);
	set_char_at_pos(ch, color, pos);
}

/** 
 * @brief Returns the character displayed at position (row, col).
 *
 * @param row Row of the character.
 * @param col Column of the character.
 *
 * @return The character at (row, col).
 */
char get_char(int row, int col) {
	int pos = ((row*CONSOLE_WIDTH) + col);
	return *(char *)(CONSOLE_MEM_BASE + (2*pos));
}

/*
 * @brief Sets the hardware cursor to the specified position
 *
 * @param position of the cursor
 * Eg: If cursor has to be places at (x, y), then the value
 * of position would be ((x*row)+y)
 *
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
	int i;

	//Copy all rows but the first one into a temporary buffer
	int temp = (2*((CONSOLE_WIDTH*CONSOLE_HEIGHT)-CONSOLE_WIDTH));
	char temp_buf[temp];
	memcpy(temp_buf, (void *)(CONSOLE_MEM_BASE+(2*CONSOLE_WIDTH)), temp);

	//Copy the temporary buffer back to the start of the console
	memcpy((void *)CONSOLE_MEM_BASE, temp_buf, temp);

	//Set the last row to empty
	for(i = 0; i < CONSOLE_WIDTH; i++) {
		int pos = ((CONSOLE_HEIGHT-1)*CONSOLE_WIDTH)+i;
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
/*void get_char_at_pos(char *ch, char *color, int pos) {
	*ch = *(char *)(CONSOLE_MEM_BASE + (2*pos));
	*color = *(char *)(CONSOLE_MEM_BASE + (2*pos+1));
}*/
