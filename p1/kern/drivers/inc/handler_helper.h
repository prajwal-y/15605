/** @file timer_driver.h
 *
 *	@brief Interface for handlers of keyboard and timer
 *
 *	@author Prajwal Yadapadithaya (pyadapad)
 *	@bug None
 **/

/**
 * @brief Interrupt handler for timer interrupts. The handler
 * saves the registers and handles control to the C timer 
 * driver function
 *
 * @return Void
 */
void timer_handler(void);

/**
 * @brief Interrupt handler for keyboard interrupts. The handler
 * saves the registers and handles control to the C keyboard
 * driver function
 *
 * @return Void
 */
void keyboard_handler(void);
