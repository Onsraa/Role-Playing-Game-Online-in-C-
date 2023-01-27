CC=gcc
CFLAGS=-I. $(shell mysql_config --cflags)
LIBS=$(shell mysql_config --libs)
DEPS := main.h Struct/Users/users.h Struct/Spells/spells.h Struct/Classes/classes.h
OBJ = main.o sql.o Struct/Users/users.o Struct/Spells/spells.o Struct/Classes/classes.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o Struct/*/*.o program