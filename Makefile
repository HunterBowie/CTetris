all:
	gcc main.c include/*.c -o output -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL3 -I include
