#### PROJECT SETTINGS ####
COMPILE_FLAGS = -std=c99 -Wall -Wextra -O3
# COMPILE_FLAGS = -std=c99 -Wall -Wextra -g
OBJECTS = main.o board.o front.o analysis.o ai.o

#### BUILDING ####
# Build main program
gobang: $(OBJECTS)
	@echo "Building main program..."
	gcc -o gobang $(OBJECTS) $(COMPILE_FLAGS)

# Compile source files
main.o: main.c board.h front.h analysis.h ai.h
	@echo "Compiling main.o ..."
	gcc -c main.c $(COMPILE_FLAGS)

front.o :front.c front.h
	@echo "Compiling front.o ..."
	gcc -c front.c $(COMPILE_FLAGS)

board.o: board.c board.h
	@echo "Compiling board.o ..."
	gcc -c board.c $(COMPILE_FLAGS)

analysis.o: analysis.c analysis.h board.h
	@echo "Compiling analysis.o ..."
	gcc -c analysis.c $(COMPILE_FLAGS)

ai.o: ai.c ai.h board.h analysis.h
	@echo "Compiling ai.o ..."
	gcc -c ai.c $(COMPILE_FLAGS)

# Clean all build files
.PHONY: clean
clean: 
	rm -f gobang $(OBJECTS)