CC=gcc
CFLAG=-Wall -DDEBUG
CLIBS=-lm
PROG=bp_mo
OBJS=bp_mo.o
ALL: $(PROG)
.c.o:
	$(CC)  -c -o $@ $< $(CFLAG) 
$(PROG):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)  $(CLIBS)
clean:
	rm -rf *~ *.o $(PROG) $(OBJS)
