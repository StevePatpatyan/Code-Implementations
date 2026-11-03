# compile clox interpreter
clox: $(wildcard *.c *.h)
	gcc -Wall -Wextra -std=c99 -g *.c -o clox

benchmarks: 
	gcc -O2 -o benchmarks benchmarks.c table.c memory.c object.c value.c