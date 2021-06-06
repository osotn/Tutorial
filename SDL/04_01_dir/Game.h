#ifndef __Game__
#define __Game__

#include <SDL.h>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

class Game
{
public:

    ~Game() {}

    static Game* Instance()
    {
        static Game* s_pInstance = 0;

        if (s_pInstance == 0)
            s_pInstance = new Game();
  
        return s_pInstance;
    }

    bool init(const char* title, int xpos, int ypos, int height, int width, int flags);

    void render();
    void update();
    void handleEvents();
    void clean();

    bool running() const { return m_bRunning; }

    SDL_Renderer* getRenderer() const { return m_pRenderer; } 

    void quit();

private:

    Game(){}

    SDL_Window * m_pWindow;
    SDL_Renderer * m_pRenderer;

    bool m_bRunning;

    int m_currentFrame;

    std::vector<GameObject*> m_gameObjects;
};

typedef Game TheGame;

#endif /* ifndef __Game__ */

