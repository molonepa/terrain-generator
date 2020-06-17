
OBJS = src/main.cpp src/noiseMapGeneration.cpp src/hydraulicErosion.cpp
TINY = src/include/TinyEngine/include/imgui/imgui.cpp src/include/TinyEngine/include/imgui/imgui_demo.cpp src/include/TinyEngine/include/imgui/imgui_draw.cpp src/include/TinyEngine/include/imgui/imgui_widgets.cpp src/include/TinyEngine/include/imgui/imgui_impl_opengl3.cpp src/include/TinyEngine/include/imgui/imgui_impl_sdl.cpp
TINYLINK = -lX11 -lpthread -lSDL2 -lnoise -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lGL -lGLEW -lboost_serialization -lboost_system -lboost_filesystem
OPENMP = -fopenmp

CC = g++ -std=c++17
COMPILER_FLAGS = -Wfatal-errors -O
LINKER_FLAGS = -I/usr/local/include -L/usr/local/lib
OBJ_NAME = main

all: $(OBJS)
			$(CC) $(OBJS) $(TINY) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(TINYLINK) $(OPENMP) -o $(OBJ_NAME)

debug: $(OBJS)
			$(CC) $(OBJS) $(TINY) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(TINYLINK) $(OPENMP) -g
