/** @file screen_painter.c
 *  @brief This file has functions to paint the different
 *  screens required for Flood-It
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug Not implemented
 */

#include "inc/game_controller.h"
#include "inc/game_strings.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

static void print_last5();

/**
 * @brief Function to paint the title screen of Flood-It
 * Paints the title of the game, and the authors name.
 * Also prints the time and score of last 5 games.
 *
 * @return Void
 */
void paint_title_screen() {
	
	clear_console();

	int row = SCREEN_HEIGHT/4;
	int col = SCREEN_WIDTH/2;

	set_cursor(row, col);
	printf("%s", str_title);

	col = SCREEN_WIDTH/4;
	set_cursor(row+2, col);
	printf("%s", str_author);

	set_cursor(row+4, col);
	printf("%s", str_start);

	print_last5();

}

void print_last5() {
	int row = SCREEN_HEIGHT/2;
	int col = SCREEN_WIDTH/3;

	set_cursor(row, col);
	printf("%s", str_last5);

	int i;
	for(i=GAME_COUNT-1; i>=0; i--) {
		if(last5[i].elapsed_time != 0) {
			set_cursor(++row, col);
			printf("Time = %d:%d Flood count = %d", 
					last5[i].elapsed_time/60, 
					last5[i].elapsed_time%60, 
					last5[i].flood_count);
		}
	}
	
}

/**
 * @brief Function to paint the board size selection screen.
 * The screen will show a list of board sizes to choose from
 * for the user.
 *
 * @return Void
 */
void paint_board_sel_screen() {
	clear_console();
	
	int row = SCREEN_HEIGHT/3;
	int col = SCREEN_WIDTH/3;

	set_cursor(row, col);
	printf("%s", str_choose_board);
	set_cursor(row+1, col);
	printf("%s", str_make_sel);

	row = row+4;

	int i;
	for(i=0; i<BOARD_SIZE_COUNT; i++) {
		set_cursor(row++, col);
		printf("(%d) %dx%d", (i+1), board_type[i], board_type[i]);
	}	
}

/**
 * @brief Function to paint the color selection screen. The 
 * screen will show the number of colors for the game that
 * the user can choose.
 *
 * @return Void
 */
void paint_color_sel_screen() {
	clear_console();
	
	int row = SCREEN_HEIGHT/3;
	int col = SCREEN_WIDTH/3;

	set_cursor(row, col);
	printf("%s", str_choose_color);
	set_cursor(row+1, col);
	printf("%s", str_make_sel);

	row = row+4;

	int i;
	for(i=0; i<COLOR_COUNT; i++) {
		set_cursor(row++, col);
		printf("(%d) %d colors", (i+1), color_count[i]);
	}
}

void paint_game_screen() {
}

void paint_pause_screen() {
}

void paint_end_screen() {
}

void paint_instr_screen() {
}
