#ifndef GLOBALS_H
#define GLOBALS_H

char* myname;

char* source_name;

int ncolors;
int clever_allocation;
int print_allocation_flag;
int target_riscv;

#define EXITCODE_NOERROR        0
#define EXITCODE_BADARGUMENTS   1
#define EXITCODE_IOERROR        2
#define EXITCODE_SCANNERERROR   3
#define EXITCODE_PARSERERROR    4
#define EXITCODE_COMPILERERROR  5

#endif
