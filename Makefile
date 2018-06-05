PROG = main
OBJS = main.o types.o gen.o calc.o
CC = gcc
CFLAGS = -Wall -O1 -O2 -O3

.SUFFIXES: .c

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $^
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm  $(OBJS) $(PROG)
