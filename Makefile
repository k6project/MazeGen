CC=g++
CC_FLAGS=-c -g
LD_FLAGS=-lboost_program_options -ljpeg
BIN=mazegen

OBJS=ascii.o jpeg.o renderer.o random.o maze_gen.o maze.o main.o

%.o : %.cpp
	$(CC) $(CC_FLAGS) $< -o $@

all: build

build: $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LD_FLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(BIN)
