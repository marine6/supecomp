CFLAGS := -Wall -Werror	-Wno-error=unused-variable -O0 -g -m64

HEADERS=ast.h \
	datatypes.h \
	expr_parser.h \
	globals.h \
	lexer.h \
	parser.h \
	tree_dump.h \
	state.h \
	elang.h elang_gen.h elang_print.h elang_run.h \
	cfg.h cfg_gen.h cfg_print.h cfg_run.h \
  cfg_liveness.h cfg_dead_assign_elimination.h \
	cfg_value_analysis.h cfg_constant_propagation.h \
	rtl.h rtl_gen.h rtl_print.h rtl_run.h \
	linear.h linear_gen.h linear_print.h linear_run.h \
  linear_liveness.h \
	regalloc.h x86gen.h riscv_gen.h

CFILES=ast.c \
  datatypes.c \
  expr_parser.c \
  globals.c \
  parser.c \
  lexer.c \
  tree_dump.c \
	state.c \
  elang_gen.c elang_print.c elang_run.c \
	cfg_gen.c cfg_print.c cfg_run.c \
  cfg_liveness.c cfg_dead_assign_elimination.c \
	cfg_value_analysis.c cfg_constant_propagation.c \
	rtl_gen.c rtl_print.c rtl_run.c \
	linear_gen.c linear_print.c linear_run.c \
  linear_liveness.c \
	regalloc.c  x86gen.c riscv_gen.c

OBJS=$(CFILES:.c=.o)

TESTS=tests/*.e

# .SUFFIXES:

all: supecomp

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c

supecomp: ${OBJS} main-supecomp.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o
	rm -rf supecomp
