#include <stdio.h>
#include <stdlib.h>


void print_long(long x){
  printf("%ld\n", x);
}

extern int supecomp_main();
int main(int argc, char* argv[]){
	for(int i = argc - 1; i >= 1; i--){
		long x = atol(argv[i]);
		asm("push %0" : "=m" (x));
	}
	printf("Result = %d\n", supecomp_main());
  return 0;
}
