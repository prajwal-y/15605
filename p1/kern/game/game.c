/** @file game.c
 *  @brief A kernel with timer, keyboard, console support
 *  This file contains the kernel's main() function.
 *  It sets up the drivers and starts the game.
 *
 *  @author Prajwal Yadapadithaya (pyadapad)
 *  @bug None
 */

#include "inc/game_controller.h"

/** @brief Kernel entrypoint.
 *  This is the entrypoint for the kernel. It simply sets up the
 *  drivers and passes control off to begin_game();
 *
 * @return Does not return
 */
int kernel_main(mbinfo_t *mbinfo, int argc, char **argv, char **envp) {
	handler_install(tick);
	enable_interrupts();
	initialize_game();
	begin_game();

	while (1) {
		continue;
	}
	return 0;
}
