/** @file game_controller.c
 *  @brief The main controller for the Flood-It game.
 *  Includes all the logic required to run the game 
 *  from start to end.
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug Not implemented
 */

#include "inc/game_controller.h"

static void init_scores(void);

/**
 * @brief This function is used to initialize the key 
 * data structures that the game relies on. This function
 * will be called by kernel_main() from game.c
 *
 * @return Void
 */
void initialize_game() {
	cur_board_type = -1; /*Setting to an invalid value*/
	cur_color_count = -1;
	cur_max_moves = -1;
	init_scores();
	switch_to_title_screen();
}

/**
 * @brief Starts the flow of the game by calling 
 * read_key_char() in key_handler.c. This method
 * should return only if the game is terminated
 * somehow.
 *
 * return Void
 */
void begin_game() {
	read_key_char();	
}

/** @brief Tick function, used to keep track of the time
 * elapsed in this real time Flood-It game. 
 *
 * @return Void
 **/
void tick(unsigned int numTicks) {
	if((cur_screen == GAME_SCREEN) && ((numTicks % 100) == 0)) {
		increment_time();
	}
	num_ticks++;
}

/**
 * @brief Initialize the last 5 scores to 0.
 *
 * @return void
 */
void init_scores() {
	int i;
	for(i=0; i<GAME_COUNT; i++) {
		last5[i].elapsed_time = 0;
		last5[i].flood_count = 0;
	}
}

/**
 * @brief Adds a score to the last5 scores list.
 * If all the last 5 scores are present, the first
 * one is removed and the new one is added.
 *
 * @param time Elapsed time of the current game
 * @param count Flood count of the current game
 *
 * @return Void
 */
void add_score(unsigned int time, unsigned int count) {
	int i, index = -1;
	for(i=0; i<GAME_COUNT; i++) {
		if(last5[i].elapsed_time == 0) {
			index = i;
			break;
		}
	}

	if(index == -1) {
		for(i=0; i<GAME_COUNT-1; i++) {
			last5[i].elapsed_time = last5[i+1].elapsed_time;
			last5[i].flood_count = last5[i+1].flood_count;
		}
		last5[i].elapsed_time = time;
		last5[i].flood_count = count;
	} else {
		last5[index].elapsed_time = time;
		last5[index].flood_count = count;
	}
}

/**
 * @brief Switches the current screen to the main title screen
 * This screen is first shown when the game is started, and also
 * can be reached from the gameplay screen, pause screen and the
 * instructions screen.
 *
 * @return Void
 */
void switch_to_title_screen() {	
	paint_title_screen();
	cur_screen = TITLE_SCREEN;
}

/**
 * @brief Switches the current screen to the board selection screen.
 * This screen can be reached only from the title screen.
 *
 * @return Void
 */
void switch_to_board_sel() {
	if(cur_screen != TITLE_SCREEN) {
		return;
	}
	paint_board_sel_screen();
	cur_screen = BOARD_SEL_SCREEN;	
}

/**
 * @brief Switches the current screen to the color selection screen.
 * This screen can be reached from only the board selection screen.
 *
 * @return Void
 */
void switch_to_color_sel() {
	if(cur_screen != BOARD_SEL_SCREEN) {
		return;
	}
	paint_color_sel_screen();
	cur_screen = COLOR_SEL_SCREEN;
}

/**
 * @brief Function to hand over the control to gameplay_handler.
 * The actual gameplay begins when start_gameplay() is invoked.
 *
 * @return Void
 */
void switch_to_game() {
	set_max_moves(); /*Set the maximum moves allowed for the game*/	
	start_gameplay();
	cur_screen = GAME_SCREEN;
}

/**
 * @brief Switches the current screen to the instructions screen.
 * Instruction screen can be reached from title screen and 
 * game play screen.
 *
 * @return Void
 */
void switch_to_instr(void) {
	cur_screen = INSTR_SCREEN;
}

/**
 * @brief Switches the current screen to the "pause" screen.
 * This screen can be reached only from the game play screen.
 *
 * @return Void
 */
void switch_to_pause(void) {
	cur_screen = PAUSE_SCREEN;
}

/**
 * @brief Switches the current screen to the end-of-game screen.
 * This screen can be reached only from gameplay screen.
 *
 * @return Void
 */
void switch_to_end(void) {
	cur_screen = END_SCREEN;
}

/**
 * @brief Sets the board size for a particular game.
 *
 * @param type_index The index of the type in the array
 * board_type
 *
 * @return Void
 */
void set_board_type(int type_index) {
	if(type_index >=0 && type_index < BOARD_SIZE_COUNT) {
		cur_board_type = board_type[type_index];
	}
}

/**
 * @brief Sets the color count for a particular game
 *
 * @param color_index The index of the color count in the
 * array color_count
 *
 * @return Void
 *
 */
void set_color_count(int color_index) {
	if(color_index >=0 && color_index < COLOR_COUNT) {
		cur_color_count = color_count[color_index];
	}
}

/**
 * @brief Sets the maximum number of moves allowed for the 
 * current game.
 *
 * @param type_index Index of the type in the array board_type
 * @param color_index Index of the count in the array color_count
 *
 * @return Void
 */
void set_max_moves() {
	int i;
	int type_index, color_index;
	for(i=0; i<BOARD_SIZE_COUNT; i++) {
		if(board_type[i] == cur_board_type) {
			type_index = i;
			break;
		}
	}
	for(i=0; i<COLOR_COUNT; i++) {
		if(color_count[i] == cur_color_count) {
			color_index = i;
			break;
		}
	}
	cur_max_moves = max_moves[type_index][color_index];
}
