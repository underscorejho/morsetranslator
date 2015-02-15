#DIR =../include
#CC=gcc
#CFLAGS=-I$(IDIR)

#ODIR=obj
#LDIR =../lib

#LIBS=-lm

#_DEPS = morse.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#_OBJ = main.o morse.o 
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


#$(ODIR)/%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#morsemake: $(OBJ)
#	gcc -o $@ $^ $(CFLAGS) $(LIBS)

#.PHONY: clean

#clean:
#	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

####################################################
## not copy and pasted #############################
####################################################

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
