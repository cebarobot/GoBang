#### PROJECT SETTINGS ####
COMPILE_FLAGS = -std=c99 -Wall -Wextra -g -O3
OBJECTS = main.o board.o

#### BUILDING ####
# Build main program
gobang: $(OBJECTS)
	@echo "Building main program..."
	gcc -o gobang $(OBJECTS) $(COMPILE_FLAGS)

# Compile source files
main.o: main.c board.h
	@echo "Compiling main.o ..."
	gcc -c main.c $(COMPILE_FLAGS)

board.o: board.c board.h
	@echo "Compiling board.o ..."
	gcc -c board.c $(COMPILE_FLAGS)


# Clean all build files
.PHONY: clean
clean: 
	rm gobang $(OBJECTS)