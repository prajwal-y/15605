/** @file key_handler.c
 *  @brief Key press handler for the game Flood it
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug Not implemented
 */

#include "inc/game_controller.h"

/*Key handler functions*/
static void handle_asdw(int);
static void handle_mark();
static void handle_selection(int);
static void handle_g();
static void handle_p();
static void handle_r();
static void handle_e();
static void handle_i();

/*Other helper functions*/
static void set_board_type_and_switch(int);
static void set_color_count_and_switch(int);

/**
 * @brief Key press handler for Flood-It
 * Reads the user input (an input character) and
 * calls the associated function with the particular
 * key.
 *
 * @retun Void
 */
void read_key_char() {

	while(1) {
		int ch = readchar();
		if(ch == -1) {
			continue;
		}

		lprintf("%c", ch);
		//Handle various operations
		switch(ch) {
			case 'A':
			case 'a':
				handle_asdw(1);
				break;
			case 'S':
			case 's':
				handle_asdw(4);
				break;
			case 'W':
			case 'w':
				handle_asdw(3);
				break;
			case 'D':
			case 'd':
				handle_asdw(2);
				break;

			case ' ':
				handle_mark();
				break;

			case '1':
				handle_selection(0);
				break;
			case '2':
				handle_selection(1);
				break;
			case '3':
				handle_selection(2);
				break;
			case '4':
				handle_selection(3);
				break;
			case '5':
				handle_selection(4);
				break;

			case 'G':
			case 'g':
				handle_g();
				break;
			case 'P':
			case 'p':
				handle_p();
				break;
			case 'R':
			case 'r':
				handle_r();
				break;
			case 'E':
			case 'e':
				handle_e();
				break;

			case 'I':
			case 'i':
				handle_i();
				break;

			default: 
				break;
		}
	}
}

/**
 * @brief Function for key presses for 'a', 's', 'd' and 'w'
 * Calls the handle_move() function with the given key code.
 *
 * @param num Key code for the type of key press
 * (a-1, d-2, w-3, s-4)
 *
 * @return Void
 */
void handle_asdw(int num) {
	if(cur_screen != GAME_SCREEN) {
		return;
	}
	handle_move(num);
}

/**
 * @brief Function to handle key press for marking a color
 * during the game. Can be invoked only from the game screen
 *
 * @return Void
 */
void handle_mark() {
	if(cur_screen != GAME_SCREEN) {
		return;
	}
	process_mark();
}

/**
 * @brief Function to handle when 'g' or 'G' is
 * pressed.
 *
 * This key can be pressed only in the title screen.
 * So this function ignores the key if the current
 * screen is not title screen.
 *
 * @return Void
 */
void handle_g() {
	if(cur_screen == TITLE_SCREEN) {
		switch_to_board_sel();		
	}
}

void handle_p() {
}

void handle_r() {
}

void handle_e() {
}

void handle_i() {
}

/**
 * @brief Function to handle a selection in board type 
 * selection and color count selection screens.
 *
 * @param index Index of the array (board_type or color_count)
 *
 * @return Void
 */
void handle_selection(int index) {	
	switch(cur_screen) {
		case BOARD_SEL_SCREEN:
			set_board_type_and_switch(index);
			break;
		case COLOR_SEL_SCREEN:
			set_color_count_and_switch(index);
			break;
		default:
			break;
	}
}

/**
 * @brief Function to set the board type and switch to
 * the color count selection screen (from the board selection screen)
 *
 * @param type_index Index into the board_type array
 *
 * @return Void
 */
void set_board_type_and_switch(int type_index) {
	set_board_type(type_index);
	switch_to_color_sel();
}

/**
 * @brief Function to set the color count and switch to
 * the game play screen (from the color count selection screen)
 *
 * @param color_index Index into the color_count array
 *
 * @return Void
 */
void set_color_count_and_switch(int color_index) {
	set_color_count(color_index);
	switch_to_game();
}
