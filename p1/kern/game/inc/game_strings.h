/** @file game_strings.h
 *  @brief All the constants used in the game
 *  are defined in this file
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug None
 */

#ifndef __game_strings_h
#define __game_strings_h

/*Ascii art*/
/* Generated using the link http://patorjk.com/software/taag */
const char *str_flood_it[] = {
" _______  _        _______  _______  ______      __________________",
"(  ____ \\( \\      (  ___  )(  ___  )(  __  \\     \\__   __/\\__   __/",
"| (    \\/| (      | (   ) || (   ) || (  \\  )       ) (      ) (",
"| (__    | |      | |   | || |   | || |   ) | _____ | |      | |",
"|  __)   | |      | |   | || |   | || |   | |(_____)| |      | |",
"| (      | |      | |   | || |   | || |   ) |       | |      | |",
"| )      | (____/\\| (___) || (___) || (__/  )    ___) (___   | |",
"|/       (_______/(_______)(_______)(______/     \\_______/   )_("
};
           
/*Title Screen strings*/
const char *str_author = "Game by Prajwal Yadapadithaya (pyadapad)";
const char *str_last5 = "Last 5 games";
const char *str_start = "g - Begin game";
const char *str_help = "h - Help";

/*Selection screen strings*/
const char *str_choose_board = "Choose the board size for the game.";
const char *str_choose_color = "Select the number of colors for the game.";
const char *str_make_sel = "Please enter the corresponding number to choose";

/*Game play screen strings*/
const char *str_game_move = "wasd = move";
const char *str_game_mark = "space = mark";
const char *str_game_pause = "p = pause";
const char *str_game_help = "h = help";
const char *str_game_quit = "q = quit";

/*Pause screen strings*/
const char *str_game_resume = "r = resume";
const char *str_game_paused = "Game paused";

/*End screen strings*/
const char *str_win = "Yay! You won :)";
const char *str_lose = "You lost :(";
const char *str_start_over = "Type 't' to go to the main screen";

/*Help screen strings*/
const char *str_instr[] = {
		"Welcome to Flood-It. The rules of the game are listed below.",
		"The rules are simple:",
		"1. Click cells. 2. Fill the board with a single color.",
		"If you manage to fill the entire board with a single color in",
		"the given number of moves, you win the game. Else, you lose.",
		"Use wasd keys to move the selection cell in the board.",
		"Use space key to fill the board with a particular color.",
		"b : back to the previous screen"};

#endif
