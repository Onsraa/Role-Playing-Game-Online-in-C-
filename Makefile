CC = gcc
CFLAGS = $(mysql_config --cflags)
LDFLAGS = $(mysql_config --libs)
TARGET = main

OBJS = main.o Struct/struct.o Struct/Classes/classes.o Struct/Element/element.o Struct/Spells/spells.o Struct/Users/users.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
