/** 
 * @file gameplay_handler.c
 * @brief The handler for the actual gameplay,
 * starting from showing the color grid to
 * winning/losing the game
 *
 * @author Prajwal Yadapadithaya (pyadapad)
 * @bug None
 */

#include <mt19937int.h>
#include "inc/game_controller.h"

#define COLOR_CODE_MULTIPLIER 16

char **grid;
int curX, curY;
int fill_count;
unsigned int moves_count;
unsigned int time_elapsed;

int toggle = 1;

/*Helper functions*/
void allocate_grid(void);
void deallocate_grid(void);
void initialize_grid(void);
void reset_variables(void);
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
	allocate_grid();
	initialize_grid();
	reset_variables();
	sgenrand(num_ticks);
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
	update_grid_position(grid, 0, 0, curX, curY);
	print_game_time(time_elapsed);
	print_game_moves(moves_count, cur_max_moves);
}

/**
 * @brief Function to end the gameplay. Control will be returned to 
 * game_controller.c by displaying end game screen
 *
 * @return Void
 */
void end_gameplay() {
	int fill_percentage = (fill_count*100)/(cur_board_type*cur_board_type);
	int success = ((moves_count<=cur_max_moves)&&(fill_percentage==100))?1:0;
	add_score(time_elapsed, fill_percentage, success);
	deallocate_grid();
	reset_variables();
	switch_to_end(success);
}

/**
 * @brief Function to quite the current game. Control will be returned
 * to game_controller.c by displaying the title screen
 */
void quit_gameplay() {
	deallocate_grid();
	reset_variables();
	switch_to_title_screen();
}

/**
 * @brief Function to initialize the color grid with random colors.
 *
 * @return Void
 */
void initialize_grid() {
	int i,j;

	for(i=0; i<cur_board_type; i++) {
		for(j=0; j<cur_board_type; j++) {
			grid[i][j] = get_random_color();
		}
	}
}

/**
 * @brief Function to reset the variables of the
 * current game.
 *
 * @return Void
 */
void reset_variables() {
	curX = 0;
	curY = 0;
	fill_count = 1;
	moves_count = 0;
	time_elapsed = 0;
}

/**
 * @brief Allocates memory for the grid required for the
 * current game. Should be called by start_gameplay()
 *
 * @return Void
 */
void allocate_grid() {
	int i;
	
	grid = (char **)malloc(sizeof(char **)*cur_board_type);

	for(i=0; i<cur_board_type; i++) {
		grid[i] = (char *)malloc(sizeof(char)*cur_board_type);
	}
}

/**
 * @brief Deallocates the memory allocated for the grid.
 * Should be called by end_gameplay()
 *
 * @return Void
 */
void deallocate_grid() {
	int i;	
	for(i=0; i<cur_board_type; i++) {
		free(grid[i]);
	}
	free(grid);
}

/**
 * @brief Function to return a random color. Used to populate the grid
 * when the game begins.
 *
 * @return char A random color
 */
char get_random_color() {
	long rand = (genrand()%cur_color_count)*COLOR_CODE_MULTIPLIER;
	return (char)rand;
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
	moves_count++;
	fill_count = fill_color(grid[curX][curY]);
	update_game_screen(grid, cur_board_type, cur_board_type, 
						time_elapsed, moves_count, cur_max_moves);

	if(fill_count == (cur_board_type*cur_board_type) 
			|| moves_count>=cur_max_moves) {
		end_gameplay();
	}
}

/**
 * @brief Function to fill color recursively in the grid
 *
 * @param oldcolor Color to be replaced
 * @param newcolor New color to be filled
 * @param x x-coordinate of the grid to be filled
 * @param y y-coordinate of the grid to be filled
 * @param visited Character array to save visited cells in the grid
 * @param change 1-change color if possible; 0-Do not change color
 *
 * @return Fill count
 */
int fill_color_recursive(char oldcolor, char newcolor, int x, int y, 
						char *visited, int change) {
	if(x<0 || y<0 || x>=cur_board_type || y>=cur_board_type
		|| (grid[x][y] != oldcolor && grid[x][y] != newcolor)) {
		return 0;
	}
	int index = (x*cur_board_type)+y;
	if((visited[index]) || (grid[x][y]==oldcolor && !change)) {
		return 0;
	}
	if(grid[x][y] == newcolor) {
		change = 0;
	} else {
		grid[x][y] = newcolor;
		change = 1;
	}

	visited[index] |= 1;
	return 1+fill_color_recursive(oldcolor, newcolor, x+1, y, visited, change)+
			fill_color_recursive(oldcolor, newcolor, x, y+1, visited, change)+
			fill_color_recursive(oldcolor, newcolor, x-1, y, visited, change)+
			fill_color_recursive(oldcolor, newcolor, x, y-1, visited, change);
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
	char *visited = (char *)calloc(cur_board_type*cur_board_type, 
									sizeof(char));
	int count = fill_color_recursive(grid[0][0], color, 0, 0, visited, 1);
	free(visited);
	return count;
}

/**
 * @brief Function to increment the elapsed time. This function will
 * be called by the callback tick funtion in game_controller.c
 */
void increment_time() {
	time_elapsed++;
	print_game_time(time_elapsed);
	toggle_grid_selection(grid, curX, curY, toggle);
	toggle = !toggle;
}
