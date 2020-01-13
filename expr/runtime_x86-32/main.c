#include <stdio.h>
#include <stdlib.h>


void print_int(int x){
  printf("%d\n", x);
}

extern int supecomp_main();
int main(int argc, char* argv[]){
	for(int i = argc - 1; i >= 1; i--){
		int x = atoi(argv[i]);
		asm("push %0" : "=m" (x));
	}
	printf("Result = %d\n", supecomp_main());
  return 0;
}
