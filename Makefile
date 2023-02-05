CC=gcc

DEPS := main.h Struct/struct.h
OBJ = main.o Struct/Users/users.o Struct/Spells/spells.o Struct/Classes/classes.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o Struct/*/*.o program