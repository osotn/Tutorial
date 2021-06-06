
CC = g++
SDL_CFLAGS = $(shell sdl2-config --cflags)
CFLAGS = -Wall -std=c++11 $(SDL_CFLAGS)
SDL_LIBS = $(shell sdl2-config --libs)
LIBS = $(SDL_LIBS) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

FILES_01_01_CPP = 01_01.cpp
FILES_01_01 = $(FILES_01_01_CPP)
FILES_01_02_CPP = 01_02.cpp
FILES_02_02 = $(FILES_02_02_CPP)
FILES_01_03_CPP = 01_03_dir/main.cpp 01_03_dir/Game.cpp 
FILES_01_03_HPP = 01_03_dir/Game.h
FILES_01_03 = $(FILES_01_03_CPP) $(FILES_01_03_HPP)
FILES_02_01_CPP = 02_01_dir/main.cpp 02_01_dir/Game.cpp 02_01_dir/TextureManager.cpp
FILES_02_01_HPP = 02_01_dir/Game.h 02_01_dir/TextureManager.h
FILES_02_01 = $(FILES_02_01_CPP) $(FILES_02_01_HPP)
FILES_03_01_CPP = 03_01_dir/main.cpp 03_01_dir/Game.cpp 03_01_dir/TextureManager.cpp \
                  03_01_dir/Player.cpp 03_01_dir/Enemy.cpp 03_01_dir/SDLGameObject.cpp
FILES_03_01_HPP = 03_01_dir/Game.h 03_01_dir/TextureManager.h \
                  03_01_dir/GameObject.h 03_01_dir/Player.h 03_01_dir/Enemy.h \
                  03_01_dir/LoaderParams.h 03_01_dir/SDLGameObject.h
FILES_03_01 = $(FILES_03_01_CPP) $(FILES_03_01_HPP)
FILES_04_01_CPP = 04_01_dir/main.cpp 04_01_dir/Game.cpp 04_01_dir/TextureManager.cpp \
                  04_01_dir/Player.cpp 04_01_dir/Enemy.cpp 04_01_dir/SDLGameObject.cpp \
                  04_01_dir/InputHandler.cpp
FILES_04_01_HPP = 04_01_dir/Game.h 04_01_dir/TextureManager.h \
                  04_01_dir/GameObject.h 04_01_dir/Player.h 04_01_dir/Enemy.h \
                  04_01_dir/LoaderParams.h 04_01_dir/SDLGameObject.h 04_01_dir/Vector2D.h \
                  04_01_dir/InputHandler.h
FILES_04_01 = $(FILES_04_01_CPP) $(FILES_04_01_HPP)




FILES = $(FILES_01_01) $(FILES_01_02) $(FILES_01_03) $(FILES_02_01)

all: $(FILES)
	$(CC) $(FILES_01_01_CPP) $(LIBS) $(CFLAGS) -o 01_01
	$(CC) $(FILES_01_02_CPP) $(LIBS) $(CFLAGS) -o 01_02
	$(CC) $(FILES_01_03_CPP) $(LIBS) $(CFLAGS) -o 01_03
	$(CC) $(FILES_02_01_CPP) $(LIBS) $(CFLAGS) -o 02_01
	$(CC) $(FILES_03_01_CPP) $(LIBS) $(CFLAGS) -o 03_01
	$(CC) $(FILES_04_01_CPP) $(LIBS) $(CFLAGS) -o 04_01
           
clean:
	rm -rf *.o 01_01 01_02 01_03 02_01 03_01 04_01

