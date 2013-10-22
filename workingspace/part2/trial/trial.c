
/*
 * trial.c: Trying to get the addresses
 *
 * Author: Mike Kasick <mkasick@andrew.cmu.edu>
 * Date:   Sat, 13 Oct 2007 23:51:13 -0400
 */

#include <exports.h>

 unsigned Install_Handler (unsigned *handlerloc, unsigned *vector);

int main(void) {
	unsigned int* handlerloc = (unsigned*)0x00000200;
	unsigned* vector = (unsigned*)0x08; 
	Install_Handler(handlerloc,vector);

	return 0;
}
unsigned Install_Handler (unsigned *handlerloc, unsigned *vector)
/* Updates contents of 'vector' to contain LDR pc,,[pc,#offset] */
/* instruction to cause long branch to address in handlerloc */
/* Function return value is original contents of 'vector'.*/
{   unsigned oldvec;
	unsigned int* temp =(unsigned int*) 0x24;
  //  vec = *handlerloc - (unsigned)vector - 0x8;
  //  if ((vec & 0xFFFFF000) != 0)
  //  {
        /* diagnose the fault */
        //exit (1);
       // printf("Please align address.\n");
        //return 0;
  //  }
  //  vec = 0xE59FF000 | vec;
    oldvec = *vector;
   // *vector = vec;
    printf("%d\n",vector);
    printf("%u\n", *temp);
    return (oldvec);
}
