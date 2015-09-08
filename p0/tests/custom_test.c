/** @file verify_test.c
 *
 * Test output format for the traceback function
 *
 * This test calls a few functions to test a bunch
 * of different outputs.
 *
 * @author Michael Ashley-Rollman(mpa)
 */

#include <stdlib.h>
#include "traceback.h"

void f6(double *d) {
	traceback(stdout);
}

void f5(void *val) 
{
	double *ptr = (double *)malloc(4);
	f6(ptr);
}

void f4(int i, float f)
{
  void *ptr = malloc(4);
  f5(ptr);
}

void f3(char c, char *str)
{
  f4(5, 35.0);
}

void f2(void)
{
  f3('\6', "test");
}

void f1(char ** array)
{
  f2();
}

int main()
{
  char *arg[] = {"cccccccccccccccccccccccccccccccccc", "bletch\x7", "\0"};

  f1(arg);

  return 0;
}
