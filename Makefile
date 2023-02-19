All: 

main: main.c
	gcc main.c -o main -lSDL2 -lSDL2_ttf

test: test.c
	gcc test.c -o test -lSDL2 -lSDL2_ttf