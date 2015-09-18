/** @file game.c
 *  @brief A kernel with timer, keyboard, console support
 *
 *  This file contains the kernel's main() function.
 *
 *  It sets up the drivers and starts the game.
 *
 *  @author Michael Berman (mberman)
 *  @bug No known bugs.
 */

#include <p1kern.h>

/* Think about where this declaration
 * should be... probably not here!
 */
void tick(unsigned int numTicks);

/* libc includes. */
#include <stdio.h>
#include <simics.h>                 /* lprintf() */
#include <malloc.h>
#include <keyhelp.h>

/* multiboot header file */
#include <multiboot.h>              /* boot_info */

/* memory includes. */
#include <lmm.h>                    /* lmm_remove_free() */

/* x86 specific includes */
#include <x86/seg.h>                /* install_user_segs() */
#include <x86/interrupt_defines.h>  /* interrupt_setup() */
#include <x86/asm.h>                /* enable_interrupts() */

#include <string.h>

char wait_char(char testc){
	char c = -1;
	while(c != testc) {
		int t = readchar();
		if(t == -1) {
			continue;
		}
		c = t;

		//printf("%d, %d, %c, %c ---  ", KH_HASDATA(c), KH_ISMAKE(c), KH_GETCHAR(c), c);
	
	};
	return c;
}


/** @brief Kernel entrypoint.
 *  
 *  This is the entrypoint for the kernel.  It simply sets up the
 *  drivers and passes control off to game_run().
 *
 * @return Does not return
 */
int kernel_main(mbinfo_t *mbinfo, int argc, char **argv, char **envp)
{
    /*
     * Initialize device-driver library.
     */
    handler_install(tick);

    /*
     * When kernel_main() begins, interrupts are DISABLED.
     * You should delete this comment, and enable them --
     * when you are ready.
     */

	enable_interrupts();

    lprintf( "Hello from a brand new kernel!" );

	clear_console();

	//MAGIC_BREAK;

	putbyte('T');


	putbytes("Hello world testing this\n new screen console\n driver this is kickass bro 2345678901 123", 87);

	printf("Testing printf\n");
	set_cursor(24, 10);

	putbytes("Hello world testing this new\n screen console\b driver this is kickass bro 2345678901 123\r", 88);

	set_cursor(5, 5);


	wait_char('t');
	//printf("%c ", wait_char('c'));
	//printf("%c ", wait_char('t'));


	/*int i = 0;
	for(i=0; i<(2*25*80); i++) {
		printf("a-a");
	}*/

    while (1) {
        continue;
    }

    return 0;
}

/** @brief Tick function, to be called by the timer interrupt handler
 * 
 *  In a real game, this function would perform processing which
 *  should be invoked by timer interrupts.
 *
 **/
void tick(unsigned int numTicks) {
	//printf("%d\n", numTicks);
}
