
OBJS = src/main.cpp src/include/engine/src/display.cpp src/include/engine/src/model.cpp src/include/engine/src/obj_loader.cpp src/include/engine/src/shader.cpp src/include/engine/src/texture.cpp
MAP = src/noiseMapGeneration.cpp
LINK = -lSDL2 -lnoise -lGL -lGLEW

CC = g++ -std=c++17
COMPILER_FLAGS = -Wfatal-errors -O
LINKER_FLAGS = -I/usr/local/include -L/usr/local/lib
OBJ_NAME = main

all: $(OBJS)
			$(CC) $(OBJS) $(MAP) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(LINK) -o $(OBJ_NAME)
debug: $(OBJS)
			$(CC) $(OBJS) $(MAP) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(LINK) -g
