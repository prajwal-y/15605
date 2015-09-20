/** @file game_controller.h
 *  @brief Header file for game_controller.c
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug None
 */

#include "game_headers.h"

#define BOARD_SIZE_COUNT 5
#define COLOR_COUNT 5

#define GAME_COUNT 5

/*2D array to keep track of maximum moves allowed*/
static const int max_moves[BOARD_SIZE_COUNT][COLOR_COUNT] = 
	{{7, 8, 10, 12, 14},
	{9, 11, 14, 16, 19},
	{11, 14, 17, 20, 23},
	{14, 17, 21, 25, 28},
	{16, 20, 25, 29, 33}};

/*Board type and color*/
static const int board_type[BOARD_SIZE_COUNT] = {6, 8, 10, 12, 14};
static const int color_count[COLOR_COUNT] = {4, 5, 6, 7, 8};

int cur_board_type; /*Stores the board size for the current game*/
int cur_color_count; /*Stores the color count for the current game*/
int cur_max_moves; /*Stores the maximum number of moves allowed for the game*/
unsigned int num_ticks; /*Stores the number of ticks so far*/

/*strict to keep track of last 5 scores*/
struct scores {
	unsigned int elapsed_time;
	unsigned int flood_count;
}last5[GAME_COUNT];

/*Enum to keep track of the current screen*/
enum SCREEN {
	TITLE_SCREEN,
	BOARD_SEL_SCREEN,
	COLOR_SEL_SCREEN,
	GAME_SCREEN,
	PAUSE_SCREEN,
	END_SCREEN,
	INSTR_SCREEN
} cur_screen;

/*Function to paint screens*/
void paint_title_screen();
void paint_board_sel_screen();
void paint_color_sel_screen();
void pause_screen();
void end_screen();
void instr_screen();
void paint_game_screen(char **, int, int, int);
void update_game_screen(char **, int, int, unsigned int, int, int);
void update_grid_position(char **, int, int, int, int);
void print_game_moves(int, int);
void print_game_time(int);

/*Key press handler*/
void read_key_char();

/*Timer callback*/
void tick(unsigned int);

/*Game initializer*/
void initialize_game(void);

/*Start game*/
void begin_game(void);

/*Controller functions*/
void switch_to_title_screen(void);
void switch_to_board_sel(void);
void switch_to_color_sel(void);
void switch_to_game(void);
void switch_to_instr(void);
void switch_to_pause(void);
void switch_to_end(void);
void add_score(unsigned int, unsigned int);

/*Value set functions*/
void set_board_type(int);
void set_color_count(int);
void set_max_moves(void);

/*Game play functions*/
void start_gameplay(void);
void resume_gameplay(void);
void end_gameplay(void);
void handle_move(int);
void process_mark(void);
void increment_time(void);
