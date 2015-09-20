/** @file gameplay_handler.c
 *  @brief The handler for the actual gameplay,
 *  starting from showing the color grid to
 *  winning/losing the game
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug Not implemented
 */

#include "inc/game_controller.h"

char **grid;
int curX, curY;
int fill_count;
int moves_count;
int time_elapsed;

/*Helper functions*/
void initialize_grid(void);
char get_random_color(void);
int fill_color(char color);

/**
 * @brief Function to initalize the data structures required
 * for the gameplay period and call the function to 
 * paint the gameplay screen.
 *
 * @Return Void
 */
void start_gameplay() {
	initialize_grid();
	curX = 0;
	curY = 0;
	fill_count = 1;
	moves_count = 0;
	time_elapsed = 0;
	paint_game_screen(grid, cur_board_type, cur_board_type, cur_max_moves);
}

/**
 * @brief Function to resume a paused gameplay. Performs the same operations
 * as start_gameplay() without re-initilazing the grid and other variables
 *
 * @return Void
 */
void resume_gameplay() {
	paint_game_screen(grid, cur_board_type, cur_board_type, cur_max_moves);
}

/**
 * @brief Function to end the gameplay. Control will be returned to 
 * game_controller.c by displaying end game screen
 *
 * @return Void
 */
void end_gameplay() {

	//TODO: Update scores
	

	free(grid[0]);
	free(grid);
	curX = 0;
    curY = 0;
    fill_count = 1;
    moves_count = 0;
    time_elapsed = 0;
}

/**
 * @brief Function to initialize the color grid with random colors.
 *
 * @return Void
 */
void initialize_grid() {
	int i,j;
	grid = (char **)malloc(sizeof(char **)*cur_board_type);
	grid[0] = (char *)malloc(sizeof(char)*cur_board_type*cur_board_type);
	for(i=0; i<cur_board_type; i++) {
		for(j=0; j<cur_board_type; j++) {
			grid[i][j] = get_random_color();
		}
	}
}

/**
 * @brief Function to return a random color. Used to populate the grid
 * when the game begins.
 *
 * @return char A random color
 */
char get_random_color() {
	//TODO:
	return BGND_GREEN;
}

/**
 * @brief Function to handle moving of the current selection in the grid.
 * Depending on the direction of movement, curX and curY values are set
 * and the selection in the grid is set appropriately.
 *
 * @param direction Direction of movement. The valid values are:
 * 1-Left; 2-Right; 3-Up; 4-Down.
 *
 * @return Void
 */
void handle_move(int direction) {
	int x = curX, y = curY;
	switch(direction) {
		case 1:
			if(curY>0) {
				curY--;
			}
			break;
		case 2:
			if(curY<(cur_board_type-1)) {
				curY++;
			}
			break;
		case 3:
			if(curX>0) {
				curX--;
			}
			break;
		case 4:
			if(curX<(cur_board_type-1)) {
				curX++;
			}
			break;
		default:
			break;
	}
	update_grid_position(grid, x, y, curX, curY);
}

/**
 * @brief Function to process the grid when a color is marked.
 * If the color marked is same as the current flood color, nothing
 * is done. Otherwise, the flood color is changed to the new color
 * using a breadth first traversal of the grid starting from the 
 * left top corner.
 *
 * @return Void
 */
void process_mark() {
	if(grid[curX][curY] == grid[0][0]) {
		return;
	}
	fill_count = fill_color(grid[curX][curY]);
	
	update_game_screen(grid, cur_board_type, cur_board_type, 
						time_elapsed, moves_count, cur_max_moves);

	if(fill_count == (cur_board_type*cur_board_type)) {
		end_gameplay();
	}
}


/**
 * @brief Function to fill the color in the grid with the new color.
 *
 * @param color Color to be used to fill the grid
 *
 * @return int Count of the number of cells filled with the new color
 * in the grid.
 */
int fill_color(char color) {
	return 1;
}

/**
 * @brief Function to increment the elapsed time. This function will
 * be called by the callback tick funtion in game_controller.c
 */
void increment_time() {
	time_elapsed++;
	print_game_time(time_elapsed);
}
