/** @file traceback_print.c
 *	@brief The traceback print function
 *	This file contains the functions for printing the 
 *	traceback details (function names, arguments and values)
 *
 *	The comments for each of the functions are added in
 *	traceback_print.h file instead of this file.
 *
 *	@author Prajwal Yadapadithaya (pyadapad)
 *	@bug In the case of invalid strings in a string array, the
 *	formatting of the string array may not work for all situations.
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "traceback_internal.h"
#include "traceback_print.h"

/*
 * The traceback tool is designed to print the stack trace
 * till the function __libc_start_main is encountered.
 * __libc_start_main() function is responsible for initializing
 * the execution environment before calling main() function of
 * the user program with the appropriate arguments. This function
 * was chosen keeping in mind the usability of this tool for user
 * programs.
 */
const char *main_fn = "__libc_start_main";

int print_func_name(void *func_addr, void *reg_ebp, FILE *fp) {
	int i;
	for(i=0; i<FUNCTS_MAX_NUM; i++) {
		if(functions[i].addr == func_addr) {
			fprintf(fp, "Function %s(", functions[i].name);
			print_params(i, reg_ebp, fp);
			fprintf(fp, "), in\n");
			if(strncmp(functions[i].name, main_fn, 4)==0) {
				return 1;
			}
			break;
		}
	}
	if(i==FUNCTS_MAX_NUM) {
		fprintf(fp, "Function %p(...), in\n", func_addr);
	}
	return 0;
}


int check_func_name(void *func_addr) {
  int i;
  for(i=0; i<FUNCTS_MAX_NUM; i++) {
		if(!functions[i].addr) {
			break;
		}
    if(functions[i].addr == func_addr) {
      return 1;
    }
  }
  return 0;
}

void print_params(int func_index, void *reg_ebp, FILE *fp) {
  int i=0;
  for(i=0; i<ARGS_MAX_NUM; i++) {
    int type = functions[func_index].args[i].type;
    int offset = functions[func_index].args[i].offset;
    char name[ARGS_MAX_NAME];
    memcpy(name, functions[func_index].args[i].name, ARGS_MAX_NAME);
    if(strlen(name)==0) {
      break;
    }
    void *value = (void *)(((char *)reg_ebp)+offset);
    if(i!=0 && type != TYPE_UNKNOWN) {
      fprintf(fp, ", ");
    }

		//If any values are illegal, just print the address as a "catch all" rule
		if(setjmp(env)) {
    	fprintf(fp, "%p", value);
			continue;
  	}
    switch(type) {
      case TYPE_CHAR:
        if(isprint(*((char *)value))) {
          fprintf(fp, "char %s='%c'", name, *((char *)value));
        } else {
          fprintf(fp, "char %s='\\%o'", name, *((char *)value));
        }
        break;
      case TYPE_INT:
        fprintf(fp, "int %s=%d", name, *((int *)value));
        break;
      case TYPE_FLOAT:
        fprintf(fp, "float %s=%f", name, *((float *)value));
        break;
      case TYPE_DOUBLE:
        fprintf(fp, "double %s=%f", name,
                *((double *)value));
        break;
      case TYPE_STRING:
				fprintf(fp, "char *%s=", name);
        if(is_printable_string((char *)(*(int *)value))) {
          char newstr[29];
          fprintf(fp, "\"%s\"",
                  string_length_handler((char *)(*(int *)value), newstr));
        } else {
          fprintf(fp, "%p", value);
        }
        break;
      case TYPE_STRING_ARRAY:
        fprintf(fp, "char **%s=", name);
        print_string_array((char **)(*(int *)value), fp);
        break;
      case TYPE_VOIDSTAR:
        fprintf(fp, "void *%s=0v%x", name, (unsigned int)value);
        break;
      case TYPE_UNKNOWN:
        fprintf(fp, "UNKNOWN *%s=%p", name, value);
        break;
      default: break;
    }
  }
  if(i == 0) {
    fprintf(fp, "void");
  }
}

char *string_length_handler(char *str, char *newstr) {
  if(strlen(str)<=25) {
    return str;
  }
  int i;
  for(i=0; i<25; i++) {
    newstr[i] = str[i];
  }
  newstr[25] = '.';
  newstr[26] = '.';
  newstr[27] = '.';
  newstr[28] = '\0';
  return newstr;
}

int is_printable_string(char *str) {
  int i=0;
  while(1) {
		if(str[i] == '\0') {
			break;
		}
    if(!isprint(str[i])) {
      return 0;
    }
    i++;
  }
  return 1;
}

void print_string_array(char **array, FILE *fp) {
  int i;
	fprintf(fp, "{");
  for(i=0; i<4; i++) {
    if(!array[i] || strlen(array[i])==0) {
      break;
    }
    if(i == 3) {
      fprintf(fp, ", ...");
      break;
    }
    if(is_printable_string(array[i])) {
      char newstr[29];
      if(i==0) {
        fprintf(fp, "\"%s\"",
                string_length_handler(array[i], newstr));
      } else {
        fprintf(fp, ", \"%s\"",
                string_length_handler(array[i], newstr));
      }
    } else {
      if(i==0) {
        fprintf(fp, "%p", (void *)array[i]);
      } else {
        fprintf(fp, ", %p", (void *)array[i]);
      }
    }
  }
	fprintf(fp, "}");
}
