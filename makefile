# based off of http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ 

CC=gcc
CFLAGS=-I. -std=c99
DEPS=morse.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

morsemake: main.o morse.o
	$(CC) -o morsemake main.o morse.o -I.

.PHONY : clean
clean :
	-rm main.o morse.o $(objects)
