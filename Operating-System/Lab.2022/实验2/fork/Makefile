all: process-fork process-exec
.PHONY : all

process-fork: process-fork.o
	gcc process-fork.o -o process-fork
process-fork.o: process-fork.c
	gcc process-fork.c -c

process-exec: process-exec.o
	gcc process-exec.o -o process-exec
process-exec.o: process-exec.c
	gcc process-exec.c -c

clean:
	rm process-fork.o process-exec.o process-fork process-exec
