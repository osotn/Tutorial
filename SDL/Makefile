
CC = g++
SDL_CFLAGS = $(shell sdl2-config --cflags)
TIXML_CFLAGS = -DTIXML_USE_STL
CFLAGS = -Wall -std=c++11 $(SDL_CFLAGS) $(TIXML_CFLAGS) -g 
SDL_LIBS = $(shell sdl2-config --libs) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
TIXML_LIBS = tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxml.cpp
LIBS = $(SDL_LIBS) $(TIXML_LIBS)

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
FILES_05_01_CPP = 05_01_dir/main.cpp 05_01_dir/Game.cpp 05_01_dir/TextureManager.cpp \
                  05_01_dir/Player.cpp 05_01_dir/Enemy.cpp 05_01_dir/SDLGameObject.cpp \
                  05_01_dir/InputHandler.cpp 05_01_dir/MenuState.cpp 05_01_dir/PlayState.cpp \
                  05_01_dir/GameStateMachine.cpp 05_01_dir/MenuButton.cpp 05_01_dir/PauseState.cpp \
                  05_01_dir/AnimatedGraphic.cpp 05_01_dir/GameOverState.cpp
FILES_05_01_HPP = 05_01_dir/Game.h 05_01_dir/TextureManager.h \
                  05_01_dir/GameObject.h 05_01_dir/Player.h 05_01_dir/Enemy.h \
                  05_01_dir/LoaderParams.h 05_01_dir/SDLGameObject.h 05_01_dir/Vector2D.h \
                  05_01_dir/InputHandler.h 05_01_dir/GameState.h 05_01_dir/MenuState.h \
                  05_01_dir/PlayState.h 05_01_dir/GameStateMachine.h 05_01_dir/MenuButton.h \
                  05_01_dir/PauseState.h 05_01_dir/AnimatedGraphic.h 05_01_dir/GameOverState.h
FILES_05_01 = $(FILES_05_01_CPP) $(FILES_05_01_HPP)
FILES_06_01_CPP = 06_01_dir/main.cpp 06_01_dir/Game.cpp 06_01_dir/TextureManager.cpp \
                  06_01_dir/Player.cpp 06_01_dir/Enemy.cpp 06_01_dir/SDLGameObject.cpp \
                  06_01_dir/InputHandler.cpp 06_01_dir/MenuState.cpp 06_01_dir/PlayState.cpp \
                  06_01_dir/GameStateMachine.cpp 06_01_dir/MenuButton.cpp 06_01_dir/PauseState.cpp \
                  06_01_dir/AnimatedGraphic.cpp 06_01_dir/GameOverState.cpp
FILES_06_01_HPP = 06_01_dir/Game.h 06_01_dir/TextureManager.h \
                  06_01_dir/GameObject.h 06_01_dir/Player.h 06_01_dir/Enemy.h \
                  06_01_dir/LoaderParams.h 06_01_dir/SDLGameObject.h 06_01_dir/Vector2D.h \
                  06_01_dir/InputHandler.h 06_01_dir/GameState.h 06_01_dir/MenuState.h \
                  06_01_dir/PlayState.h 06_01_dir/GameStateMachine.h 06_01_dir/MenuButton.h \
                  06_01_dir/PauseState.h 06_01_dir/AnimatedGraphic.h 06_01_dir/GameOverState.h \
                  06_01_dir/BaseCreator.h 06_01_dir/PlayerCreator.h 06_01_dir/EnemyCreator.h \
                  06_01_dir/MenuButtonCreator.h 06_01_dir/AnimatedGraphicCreator.h \
                  06_01_dir/GameObjectFactory.h
FILES_06_01 = $(FILES_06_01_CPP) $(FILES_06_01_HPP)



FILES = $(FILES_01_01) $(FILES_01_02) $(FILES_01_03) $(FILES_02_01) $(FILES_03_01) $(FILES_04_01) $(FILES_05_01) \
        $(FILES_06_01)

all: $(FILES)
	$(CC) $(FILES_01_01_CPP) $(LIBS) $(CFLAGS) -o 01_01
	$(CC) $(FILES_01_02_CPP) $(LIBS) $(CFLAGS) -o 01_02
	$(CC) $(FILES_01_03_CPP) $(LIBS) $(CFLAGS) -o 01_03
	$(CC) $(FILES_02_01_CPP) $(LIBS) $(CFLAGS) -o 02_01
	$(CC) $(FILES_03_01_CPP) $(LIBS) $(CFLAGS) -o 03_01
	$(CC) $(FILES_04_01_CPP) $(LIBS) $(CFLAGS) -o 04_01
	$(CC) $(FILES_05_01_CPP) $(LIBS) $(CFLAGS) -o 05_01
	$(CC) $(FILES_06_01_CPP) $(LIBS) $(CFLAGS) -o 06_01
            
clean:
	rm -rf *.o 01_01 01_02 01_03 02_01 03_01 04_01 05_01 06_01

