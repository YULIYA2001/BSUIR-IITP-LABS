all: build run clean
build: main.c func.c
	gcc -Wall -O0 -g3 -DDEBUG main.c func.c -o task.exe
	
run: task.exe
	./task.exe
	
clean: 
	rm -rf *.o task.exe