OS = $(shell uname -s)
all: program
ifeq ($(OS), Darwin)
    CC=gcc
    CFLAGS+=$(shell pkg-config --cflags mysqlclient)
    CFLAGS += -I/opt/local/include
    LIBS+=$(shell pkg-config --libs mysqlclient)
   	CFLAGS+=$(shell pkg-config --cflags json-c)
  	LIBS+=$(shell pkg-config --libs json-c)

else
    CC=gcc
    CFLAGS=-I. $(shell mysql_config --cflags)
    LIBS=$(shell mysql_config --libs)
    CFLAGS=-I. $(shell json-c-config --cflags)
    LIBS=$(shell json-c-config --libs)
endif
DEPS := main.h Struct/Users/users.h Struct/Spells/spells.h Struct/Classes/classes.h
OBJ = main.o sql.o Struct/Users/users.o Struct/Spells/spells.o Struct/Classes/classes.o Save/save.o Settings/settings.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o Struct/*/*.o program