CC = gcc
DEBUG = -g -pthread

CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wextra \
        -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
        -Wdeclaration-after-statement -Wunsafe-loop-optimizations $(DEFINES) \
        -Wno-return-local-address -Wuninitialized -Wunused -pthread \
		# -Werror

PROG = primesMT

all: $(PROG)

$(PROG): main.o  
	$(CC) $(CFLAGS) -o $(PROG) main.c
	chmod a+rx,g-w $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f psush *.o *~ \#*

canvas:
	make clean
	cd ..; tar --exclude-backups --exclude-vcs -c -a -f ./${LOGNAME}-lab5.tar.gz $(DIR)



#PROG = primesMT
#
#all: main.o #$(PROG)
#
#$(PROG): main.o #$(PROG).o 
#	$(CC) $(CFLAGS) -o $@ $^
#	chmod a+rx,g-w $@
#
#main.o: main.c #$(PROG).h
#	$(CC) $(CFLAGS) -c $<
#
##$(PROG).o: $(PROG).c $(PROG).h makefile
##	$(CC) $(CFLAGS) -c $<
#
#.PHONY: clean
#
#clean:
#	rm -f psush *.o *~ \#*
#
#canvas:
#	make clean
#	cd ..; tar --exclude-backups --exclude-vcs -c -a -f ./${LOGNAME}-lab5.tar.gz $(DIR)
#
#