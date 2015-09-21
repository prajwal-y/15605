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

#define GRID_LEFT_MARGIN 15
#define GRID_TOP_MARGIN 5

#define SPACE ' '

/*Helper functions*/
static void print_last5(int);
static void print_grid_boundary(int, int);
static void print_grid(char **, int, int);
static void set_grid_selection(char **, int, int);
static void unset_grid_selection(char **, int, int);
static void print_game_info(void);

/**
 * @brief Function to paint the title screen of Flood-It
 * Paints the title of the game, and the authors name.
 * Also prints the time and score of last 5 games.
 *
 * @return Void
 */
void paint_title_screen() {
	
	clear_console();

	hide_cursor();

	int row = SCREEN_HEIGHT/8;
	int col = SCREEN_WIDTH/8;

	int i;
	for(i=0; i<8; i++) {
		set_cursor(row++, col);
		printf("%s", str_flood_it[i]);
	}

	col = SCREEN_WIDTH/3;
	set_cursor(row+2, col);
	printf("%s", str_author);

	col = SCREEN_WIDTH/6;
	set_cursor(row+4, col);
	printf("%s", str_start);
	set_cursor(row+5, col);
	printf("%s", str_help);

	print_last5(row+4);

}

void print_last5(int row) {
	int col = (2*SCREEN_WIDTH)/3;

	set_cursor(row++, col);
	printf("%s", str_last5);
	
	set_cursor(row++, col);
	printf("------------");

	int i;
	for(i=GAME_COUNT-1; i>=0; i--) {
		if(last5[i].elapsed_time != 0) {
			set_cursor(row++, col);
			if(last5[i].win) {
				draw_char(row, col-1, 'W', BGND_BLACK|BGND_GREEN);
			} else {
				draw_char(row, col-1, 'L', BGND_BLACK|BGND_RED);
			}
			set_cursor(row, col+2);
			printf("T(m:s)=%d:%02d F(%%)=%d%%", last5[i].elapsed_time/60, last5[i].elapsed_time%60, last5[i].flood_percentage);
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
	int col = SCREEN_WIDTH/5;

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
	int col = SCREEN_WIDTH/5;

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

/**
 * @brief Function to paint the gameplay screen. Displays the
 * initial color grid and other details of the game.
 *
 * @param grid 2D array containing the grid colors
 * @param length Length of the grid
 * @param height Height of the grid
 * @param maxmoves Maximum number of moves allowed for the game
 *
 * @return Void
 */
void paint_game_screen(char **grid, int length, int height, int maxmoves) {
	clear_console();
	print_grid_boundary(length+1, height);
	print_grid(grid, length, height);
	set_grid_selection(grid, 0, 0);
	print_game_time(0);
	print_game_moves(0, maxmoves);
	print_game_info();
}

/**
 * @brief Function to update the gameplay screen with new data
 * in the grid. Also update the game progress details such as time
 * and number of moves.
 *
 * @param grid 2D array containing the grid colors
 * @param length Length of the grid
 * @param height Height of the grid
 * @param time Time elapsed so far in the current game
 * @param moves Number of moves performed in the current game
 * @param maxmoves Maximum number of moves allowed for the game
 *
 * @return Void
 */
void update_game_screen(char **grid, int length, int height, 
						unsigned int time, int moves, int maxmoves) {
	print_grid(grid, length, height);
	print_game_time(time);
	print_game_moves(moves, maxmoves);
}

/**
 * @brief Function to update the current selection in the grid.
 * This function restores the color of the previous selection in
 * the grid, and updates the color of the new selection.
 *
 * @param oldX Row of previous selection.
 * @param oldY Column of previous selection.
 * @param newX Row of the new selection.
 * @param newY Column of the new selection.
 *
 * @return Void
 */
void update_grid_position(char **grid, int oldX, int oldY, 
							int newX, int newY) {
	unset_grid_selection(grid, oldX, oldY);
	set_grid_selection(grid, newX, newY);
}

/**
 * @brief Function to print the boundary required for the grid.
 *
 * @param length Length of the boundary
 * @param height Height of the boundary
 *
 * @return Void
 */
void print_grid_boundary(int length, int height) {

	int i;

	set_cursor(GRID_TOP_MARGIN-1, GRID_LEFT_MARGIN);
	printf("+");
	set_cursor(GRID_TOP_MARGIN-1, GRID_LEFT_MARGIN+length);
	printf("+");
	set_cursor(GRID_TOP_MARGIN+height, GRID_LEFT_MARGIN);
	printf("+");
	set_cursor(GRID_TOP_MARGIN+height, GRID_LEFT_MARGIN+length);
	printf("+");

	for(i=GRID_TOP_MARGIN; i<GRID_TOP_MARGIN+height; i++) {
		set_cursor(i, GRID_LEFT_MARGIN);
		printf("|");
		set_cursor(i, GRID_LEFT_MARGIN+length);
		printf("|");
	}

	for(i=GRID_LEFT_MARGIN+1; i<GRID_LEFT_MARGIN+length; i++) {
		set_cursor(GRID_TOP_MARGIN-1, i);
		printf("-");
		set_cursor(GRID_TOP_MARGIN+height, i);
		printf("-");
	}

}

/**
 * @brief Function to paint the grid insite the grid boundary.
 *
 * @param grid 2D array containing the color of each cell in the grid
 * @param length Length of the grid
 * @param height Height of the grid
 *
 * @return Void
 */
void print_grid(char **grid, int length, int height) {
	int i, j;
	for(i=GRID_TOP_MARGIN; i<GRID_TOP_MARGIN+height; i++) {
		for(j=GRID_LEFT_MARGIN; j<GRID_LEFT_MARGIN+length; j++) {
			draw_char(i, j, SPACE,
					grid[i-GRID_TOP_MARGIN][j-GRID_LEFT_MARGIN]);
		}
	}
}

/**
 * @brief Function to set and unset the current selection.
 * This is used by gameplay_handler to generate blinking effect
 * of the selected cell.
 *
 * @param grid 2D array containing the color of each cell in the grid
 * @param x Value of row in the grid
 * @param y value of column in the grid
 * @param set 1:Set; 0:unset
 *
 * @return Void
 */
void toggle_grid_selection(char **grid, int x, int y, int set) {
	if(set) {
		set_grid_selection(grid, x, y);
	} else {
		unset_grid_selection(grid, x, y);
	}
}

/**
 * @brief Function to set the selection in the grid
 * Sets the selection to blinking.
 *
 * @param x Value of row in the grid to be selected
 * @param y Value of column in the grid to be selected
 *
 * @return Void
 */
void set_grid_selection(char **grid, int x, int y) {
	draw_char(GRID_TOP_MARGIN+x, GRID_LEFT_MARGIN+y, SPACE, grid[x][y]|BLINK);
}

/**
 * @brief Function to unset the selection in the grid at a 
 * given location
 *
 * @param x Value of row in the grid to be selected
 * @param y Value of column in the grid to be selected
 *
 * @return Void
 */
void unset_grid_selection(char **grid, int x, int y) {
	draw_char(GRID_TOP_MARGIN+x, GRID_LEFT_MARGIN+y, SPACE, grid[x][y]);
}

/**
 * @brief Function to print the number of moves
 * performed so far in the game
 *
 * @param moves Number of moves performed so far
 * @param maxmoves Maximum number of moves allowed for the game
 *
 * @return Void
 */
void print_game_moves(int moves, int maxmoves) {	
	int row = SCREEN_HEIGHT/3;
	int col = (2*SCREEN_WIDTH)/3;
	
	set_cursor(row+1, col);
	printf("Moves = %d/%d", moves, maxmoves);
}

/**
 * @brief Function to print the time elapsed so far
 * performed so far in the game
 *
 * @param time Time elapsed in the game so far.
 *
 * @return Void
 */
void print_game_time(int time) {
	int row = SCREEN_HEIGHT/3;
	int col = (2*SCREEN_WIDTH)/3;
	
	set_cursor(row, col);
	printf("Time elapsed = %d:%02d", (time/60), (time%60));
}

/**
 * @brief Function to print the static info for the game such as
 * key press information and other useful info.
 *
 * @return Void
 */
void print_game_info() {
	int row = SCREEN_HEIGHT/3;
	int col = (2*SCREEN_WIDTH)/3;
	
	set_cursor(row+2, col);
	printf("%s", str_game_move);

	set_cursor(row+3, col);
	printf("%s", str_game_mark);

	set_cursor(row+4, col);
	printf("%s", str_game_pause);

	set_cursor(row+5, col);
	printf("%s", str_game_help);
	
	set_cursor(row+6, col);
	printf("%s", str_game_quit);
}

/**
 * @brief Function to print the pause screen of the game.
 * Shows options to resume and end the current game.
 *
 * @return Void
 */
void paint_pause_screen() {
	clear_console();

	int row = SCREEN_HEIGHT/3;
	int col = SCREEN_WIDTH/5;

	set_cursor(row, col);
	printf("%s", str_game_paused);

	set_cursor(row+2, col);
	printf("%s", str_game_resume);
	
	set_cursor(row+4, col);
	printf("%s", str_game_quit);
}

/**
 * @brief Function to print the end screen of the current game.
 * Shows the result of the current game.
 *
 * @param success 1 if won, 0 if lost
 *
 * @return Void
 */
void paint_end_screen(int success) {
	clear_console();

	int row = SCREEN_HEIGHT/3;
	int col = SCREEN_WIDTH/5;	

	set_cursor(row, col);
	if(success) {
		printf("%s", str_win);	
	} else {
		printf("%s", str_lose);
	}

	set_cursor(row+2, col);
	printf("%s", str_start_over);
}

/**
 * @brief Function to print the instructions of the game.
 *
 * @return Void
 */
void paint_instr_screen() {
	clear_console();
	int row = SCREEN_HEIGHT/4;
    int col = SCREEN_WIDTH/5;

	int i;
	for(i=0; i<8; i++) {
		set_cursor(row++, col);
		printf("%s", str_instr[i]);
	}
}
