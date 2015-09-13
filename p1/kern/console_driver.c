/** @file console_driver.c 
 *
 *  @brief Implementation of the console driver code.
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug Not implemented
 */

#include <p1kern.h>
#include <stdio.h>

int putbyte(char ch) {
	return 0; 
}

void putbytes(const char *s, int len) {
}

int set_term_color(int color) {
	return 0;
}

void get_term_color(int *color) {
}

int set_cursor(int row, int col) {
	return 0;
}

void get_cursor(int *row, int *col) {
}

void hide_cursor() {
}

void show_cursor() {
}

void clear_console() {
}

void draw_char(int row, int col, int ch, int color) {
}

char get_char(int row, int col) {
	return 0;
}
