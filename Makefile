CC=gcc
CFLAGS=-I$(IDIR) -L$(LDIR)

IDIR =./raylib/include
LDIR =./raylib/lib

LIBS= -l:libraylib.so -lm -lGL -lpthread -ldl 

DEEZ = -Wl,-rpath=./raylib/lib/
ERRORS = -Wall -Werror

gof:
	$(CC) $(ERRORS) gof.c -o gof $(DEEZ) $(CFLAGS) $(LIBS)

clean: ./gof 
	rm ./gof
