/** 
 * @file traceback_print.h
 * @brief Function prototype(s) for printing traceback
 *
 * @author Prajwal Yadapadithaya (pyadapad)
 */

#ifndef __traceback_print_h_
#define __traceback_print_h_

#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

/** 
 * 	@brief prints the function name and invokes printing parameters
 * 	   for the function
 *  
 *  @param func_addr Starting address of the function to be printed
 *  @param reg_ebp The pointer to the current EBP
 *  @param fp The file pointer to the file where printing has to be done.
 *  @return 1 if the function is "main", 0 otherwise.
 */
int print_func_name(void *func_addr, void *reg_ebp, FILE *fp);


/** 
 *	@brief Checks if the function with the given starting address
 *				is present in the function table.
 *  
 *  @param func_addr Starting address of the function to be printed
 *  @return 1 if the function is "main", 0 otherwise.
 */
int check_func_name(void *func_addr);

/**
 *	@brief Prints the parameters of the function with the given index
 *	from the function table.
 *
 *	@param func_index	Index of the function in the function table.
 *	@param reg_ebp The pointer to the current EBP
 *	@param fp File pointer to the file where printing must be done.
 *	@return void
 */
void print_params(int func_index, void *reg_ebp, FILE *fp);

/**
 *	@brief Checks if the given string is a "printable" string
 *
 *	@param str String to be checked
 *	@return 1 if string is printable; 0 otherwise
 */
int is_printable_string(char *str);

/**
 *	@brief Prints a string array
 *
 *	@param array The array of strings to be printed
 *	@fp File pointer to the file where printing must be done.
 *	@return void
 */
void print_string_array(char **array, FILE *fp);

/**
 *	@brief Checks strings for length>25 before printing
 *
 *	@param str String to be checked
 *	@param newstr String to be returned
 *	@return String to be printed
 */
char *string_length_handler(char *str, char *newstr);

#endif /* __traceback_print_h_ */

