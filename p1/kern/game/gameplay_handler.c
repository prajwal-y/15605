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

/*Helper functions*/
void initialize_grid(void);
char get_random_color(void);

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
	paint_game_screen(grid, cur_board_type, cur_board_type, cur_max_moves);
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
