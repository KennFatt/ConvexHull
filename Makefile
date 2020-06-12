# Compiler
CC = clang++
# Compile flags
CFLAGS = -Wall -g -std=c++17
# Libraries
CLIBS = -lsfml-window -lsfml-graphics -lsfml-system

# Compile dirs
COMPILE_DIRS = out/objects
# Executable dirs
EXECUTABLE_DIRS = out

all: main.o Renderer.o
	${CC} ${COMPILE_DIRS}/*.o -o ${EXECUTABLE_DIRS}/convexhull.out ${CLIBS}

clean:
	rm -rf ${COMPILE_DIRS}/*.o

main.o: main.cc
	${CC} ${CFLAGS} -c $< -o ${COMPILE_DIRS}/$@

Renderer.o: src/Renderer.cc
	${CC} ${CFLAGS} -c $< -o ${COMPILE_DIRS}/$@