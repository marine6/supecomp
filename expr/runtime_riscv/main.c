#include <stdio.h>
#include <stdlib.h>


void print_int(int x){
  printf("%d\n", x);
}

extern int supecomp_main();
int main(int argc, char* argv[]){
	for(int i = argc - 1; i >= 1; i--){
		int x = atoi(argv[i]);
    asm("addi sp, sp, -8");
		asm("sw %0, 0(sp)" : "=r" (x));
	}
  int r = supecomp_main();
  int n = (argc - 1) * 8;
  asm("add sp, sp, %0" : "=r" (n));
  printf("Result = %d\n", r);

  return 0;
}
