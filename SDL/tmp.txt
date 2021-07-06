#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_flip = SDL_FLIP_HORIZONTAL;
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);
    InputHandler();
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    SDLGameObject::update();
}

void Enemy::clean()
{
}

void Enemy::InputHandler()
{
    if (TheInputHandler::Instance()->joysticksInitialised())
    {
        m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0,2));
        m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0,2));
    }

    Vector2D * vec = TheInputHandler::Instance()->getMousePosition();
    m_acceleration = (*vec - m_position) / 100;
}

#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:

    Enemy(const LoaderParams* pParems);
     
    virtual void draw();
    virtual void update();
    virtual void clean();

private:

    void InputHandler();
};

#endif

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{

    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

        if(m_pWindow != 0)
        {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);


            if (m_pRenderer != 0)
            {
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
            }
        }
    }
    else
    {
        return false;
    }

    m_bRunning = true;

    if( ! TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";

    m_gameObjects.push_back(new Player(new LoaderParams(0, 0, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(0, 100, 128, 82, "animate")));

    TheInputHandler::Instance()->initialiseJoysticks();

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());
    
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

//    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
//    {
//        m_gameObjects[i]->draw();
//    }

    m_pGameStateMachine->render();

    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
//    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
//    {
//        m_gameObjects[i]->update();
//    }

    m_pGameStateMachine->update();
}

void Game::clean()
{
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
}

void Game::quit()
{
    m_bRunning = false;
}

#ifndef __Game__
#define __Game__

#include <SDL.h>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "GameStateMachine.h"

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

    GameStateMachine * m_pGameStateMachine;
};

typedef Game TheGame;

#endif /* ifndef __Game__ */

#ifndef __GameObject__
#define __GameObject__

#include "LoaderParams.h"

class GameObject
{
public:

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

protected:

    GameObject(const LoaderParams* pParams) {}
    virtual ~GameObject() {}
};

#endif

#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <string>

class GameState
{
public:
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;

    virtual ~GameState() {}
};

#endif

#include "GameStateMachine.h"

void GameStateMachine::update()
{
    if (!m_gameStates.empty())
    {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render()
{
    if (!m_gameStates.empty())
    {
        m_gameStates.back()->render();
    }
}

void GameStateMachine::pushState(GameState *pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->onExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::changeState(GameState *pState)
{
    if (!m_gameStates.empty())
    {
        if (m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }

        if (m_gameStates.back()->onExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }

    m_gameStates.push_back(pState);

    m_gameStates.back()->onEnter();
}
 
#ifndef __GAME_STATE_MACHINE__
#define __GAME_STATE_MACHINE__

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:

    void update();
    void render();
    void pushState(GameState *pState);
    void changeState(GameState *pState);
    void popState();

private:
    std::vector<GameState*> m_gameStates;
};

#endif
#include "InputHandler.h"
#include "Game.h"
#include <iostream>

void InputHandler::initialiseJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    if (SDL_NumJoysticks() > 0)
    {
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            
            if (joy != NULL) {
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));

                std::vector<bool> tempButtons;

                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
                    tempButtons.push_back(false);

                m_buttonStates.push_back(tempButtons);

                std::cout << "Opened Joystick " << i <<
                             " Name: " << SDL_JoystickNameForIndex(i) <<
                             " Number of Axes: " <<  SDL_JoystickNumAxes(joy) <<
                             " Number of Buttons: " << SDL_JoystickNumButtons(joy) <<
                             " Number of Balls: " <<  SDL_JoystickNumBalls(joy) << 
                             " Number of Hats: " << SDL_JoystickNumHats(joy) << std::endl;
            }
            else {
                std::cout << SDL_GetError();
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;

        std::cout << "Initialised " << m_joysticks.size() << " joystick(s)" << std::endl;
    }
    else
    {
        m_bJoysticksInitialised = false;
    }

    for (int i = 0; i < 3; i++)
        m_mouseButtonStates.push_back(false);
}

void InputHandler::clean()
{
    if (! m_bJoysticksInitialised)
        return;

    for (int i = 0; i < SDL_NumJoysticks(); i++)
        SDL_JoystickClose(m_joysticks[i]);
}

void InputHandler::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        m_keystates = SDL_GetKeyboardState(0);

        if (event.type == SDL_QUIT)
            TheGame::Instance()->quit();

        if(event.type == SDL_JOYAXISMOTION) {
            int whichOne = (int) event.jaxis.which;

            if (event.jaxis.axis == 0) {
                if (event.jaxis.value > m_joystickDeadZone)
                    m_joystickValues[whichOne].first->setX(1);
                else if (event.jaxis.value < -m_joystickDeadZone)
                    m_joystickValues[whichOne].first->setX(-1);
                else
                    m_joystickValues[whichOne].first->setX(0);
            }

            if (event.jaxis.axis == 1) {
                if (event.jaxis.value > m_joystickDeadZone)
                    m_joystickValues[whichOne].first->setY(1);
                else if (event.jaxis.value < -m_joystickDeadZone)
                    m_joystickValues[whichOne].first->setY(-1);
                else
                    m_joystickValues[whichOne].first->setY(0);
            }

            if (event.jaxis.axis == 2) {
                if (event.jaxis.value > m_joystickDeadZone)
                    m_joystickValues[whichOne].second->setX(1);
                else if (event.jaxis.value < -m_joystickDeadZone)
                    m_joystickValues[whichOne].second->setX(-1);
                else
                    m_joystickValues[whichOne].second->setX(0);
            }

            if (event.jaxis.axis == 5) {
                if (event.jaxis.value > m_joystickDeadZone)
                    m_joystickValues[whichOne].second->setY(1);
                else if (event.jaxis.value < -m_joystickDeadZone)
                    m_joystickValues[whichOne].second->setY(-1);
                else
                    m_joystickValues[whichOne].second->setY(0);
            }


            if ((int)event.jaxis.axis <= 5)
            std::cout << "joy axis motion, which =  " << (int) event.jaxis.which <<
                         "axis num = " << (unsigned) event.jaxis.axis <<
                         "value = " << (signed) event.jaxis.value << std::endl;
        }

        if (event.type == SDL_JOYBUTTONDOWN) {
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = true;
            std::cout << "button  " << (int) event.jbutton.button << " DOWN" << std::endl;
        }

        if (event.type == SDL_JOYBUTTONUP) {
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = false;
            std::cout << "button  " << (int) event.jbutton.button << " UP" << std::endl;
        }

        if(event.type == SDL_JOYHATMOTION) {
            std::cout << "joy hat motion, which =  " << (int) event.jhat.which <<
                         "hat num = " << (unsigned) event.jhat.hat <<
                         "value = " << (signed) event.jhat.value << std::endl;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {

            std::cout << "Mouse button  " << (int) event.button.button << " DOWN" << std::endl;

            if (event.button.button == SDL_BUTTON_LEFT)
                m_mouseButtonStates[LEFT] = true;

            if (event.button.button == SDL_BUTTON_MIDDLE)
                m_mouseButtonStates[MIDDLE] = true;

            if (event.button.button == SDL_BUTTON_RIGHT)
                m_mouseButtonStates[RIGHT] = true;
        }

        if (event.type == SDL_MOUSEBUTTONUP) {

            std::cout << "Mouse button  " << (int) event.button.button << " UP" << std::endl;

            if (event.button.button == SDL_BUTTON_LEFT)
                m_mouseButtonStates[LEFT] = false;

            if (event.button.button == SDL_BUTTON_MIDDLE)
                m_mouseButtonStates[MIDDLE] = false;

            if (event.button.button == SDL_BUTTON_RIGHT)
                m_mouseButtonStates[RIGHT] = false;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            m_mousePosition.setX(event.motion.x);
            m_mousePosition.setY(event.motion.y);

            std::cout << "Mouse motion: x = " << event.motion.x << " y = " << event.motion.y << std::endl;
        }
    }
}

int InputHandler::xvalue(int joy, int stick)
{
    if (joy >= m_joystickValues.size())
        return 0;

    if (stick == 1)
        return m_joystickValues[joy].first->getX();

    if (stick == 2)
        return m_joystickValues[joy].second->getX();

    return 0; 
}

int InputHandler::yvalue(int joy, int stick)
{
    if (joy >= m_joystickValues.size())
        return 0;

    if (stick == 1)
        return m_joystickValues[joy].first->getY();

    if (stick == 2)
        return m_joystickValues[joy].second->getY();

    return 0; 
}

#ifndef __InputHandler__
#define __InputHandler__

#include <SDL.h>
#include <vector>
#include <utility>
#include "Vector2D.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        static InputHandler* s_pInstance = 0;

        if (s_pInstance == 0)
            s_pInstance = new InputHandler();

        return s_pInstance;
    }

    void update();
    void clean();

    void initialiseJoysticks();

    bool joysticksInitialised() { return m_bJoysticksInitialised; }

    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

    bool getButtonState(int joy, int buttonNumber)
    {
        return m_buttonStates[joy][buttonNumber];
    }

    bool getMouseButtonState(int buttonNumber) {
        return m_mouseButtonStates[buttonNumber];
    }

    Vector2D* getMousePosition()
    {
        return &m_mousePosition;
    }

    bool isKeyDown(SDL_Scancode key)
    {
        if (m_keystates)
            return (m_keystates[key] == 1);
        
         return false;
    }

private:

    InputHandler() {}
    ~InputHandler() {}
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialised;

    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    std::vector<bool> m_mouseButtonStates;
    Vector2D m_mousePosition;
    const Uint8* m_keystates;

    const int m_joystickDeadZone = 10000;
};

typedef InputHandler TheInputHandler;

#endif

#ifndef __LoaderParams__
#define __LoaderParams__

#include <string> 

class LoaderParams
{
public:

    LoaderParams(int x, int y, int width, int height, std::string textureID)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID)
    {
    }

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    std::string getTextureID() const { return m_textureID; }

private:

    int m_x;
    int m_y;

    int m_width;
    int m_height;

    std::string m_textureID;
};

#endif

#include <iostream>
#include <SDL.h>
#include "Game.h"


const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main()
{
    std::cout << "game init attempt...\n";
    if (TheGame::Instance()->init("Chapter 3: Working with Game Objects",
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  640, 480, SDL_WINDOW_SHOWN))
    {
        std::cout << "game init success!\n";

        Uint32 frameStart, frameTime;

        while (TheGame::Instance()->running())
        {
            frameStart = SDL_GetTicks();

            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));   
            }
        }

        std::cout << "game closing...\n";    
        TheGame::Instance()->clean();
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    return 0;
}

#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

    if (pMousePos->getX() < (m_position.getX() + m_width) &&
        pMousePos->getX() > m_position.getX() &&
        pMousePos->getY() < (m_position.getY() + m_height) &&
        pMousePos->getY() > m_position.getY())
    {
        m_currentFrame = MOUSE_OVER;

        if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_currentFrame = CLICKED;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}

#ifndef __MENU_BUTTON__
#define __MENU_BUTTON__

#include "SDLGameObject.h"
#include <vector>

enum button_state
{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class MenuButton : public SDLGameObject
{
public:

    MenuButton(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif

#include "MenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MenuState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    
    if (!TheTextureManager::Instance()->load("assets/button.png", "playbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/exit.png", "exitbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"));
    GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"));

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

    std::cout << "exiting MenuState\n";
    return true;
}

#ifndef __MENU_STATE__
#define __MENU_STATE__

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class MenuState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_menuID; }

private:

    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};

#endif

#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);

    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

    handleInput();
    SDLGameObject::update();
}

void Player::clean()
{
}

void Player::handleInput()
{
    if (TheInputHandler::Instance()->joysticksInitialised())
    {
        m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0,1));
        m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0,1));
    }

    //Vector2D * vec = TheInputHandler::Instance()->getMousePosition();
    //m_velocity = (*vec - m_position) / 100;

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
        m_velocity.setX(2);

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
        m_velocity.setX(-2);

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
        m_velocity.setY(-2);

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
        m_velocity.setY(2);
}   

#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:

    Player(const LoaderParams* pParems);

    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    void handleInput();
};

#endif

#include "PlayState.h"

#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{

}

void PlayState::render()
{

}

bool PlayState::onEnter()
{
    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit()
{
    std::cout << "exiting PlayState\n";
    return true;
}

#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include "GameState.h"

class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_playID; }

private:

    static const std::string s_playID;

};

#endif

#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams),
    m_position(pParams->getX(), pParams->getY()), m_velocity(0,0), m_acceleration(0,0)
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 1;
    m_currentFrame = 1;

    m_flip = SDL_FLIP_NONE;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_flip);
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;

    m_position.setX( (int)m_position.getX() % 500 );
    m_position.setY( (int)m_position.getY() % 400 );
}

void SDLGameObject::clean()
{
}

#ifndef __SDLGameObject__
#define __SDLGameObject__

#include <SDL.h>
#include <string>
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject: public GameObject
{
public:

    SDLGameObject(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

protected:

    std::string m_textureID;

    int m_currentFrame;
    int m_currentRow;

    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;

    SDL_RendererFlip m_flip;
};

#endif

#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

    if(pTempSurface == 0)
        return false;

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture == 0)
        return false;

    m_textureMap[id] = pTexture;

    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip); 
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip); 
}

void TextureManager::clearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}

#ifndef __TextureManager__
#define __TextureManager__

#include <string>
#include <map>
#include <SDL.h>

class TextureManager
{
public:

    static TextureManager* Instance()
    {
        static TextureManager* s_pInstance = 0;

        if (s_pInstance == 0)
            s_pInstance = new TextureManager();

        return s_pInstance;
    }

    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void clearFromTextureMap(std::string id);

private:
    TextureManager() {}

    std::map<std::string, SDL_Texture*> m_textureMap; 
};

typedef TextureManager TheTextureManager;

#endif
#ifndef __Vector2D__
#define __Vector2D__

#include <math.h>

class Vector2D
{
public:

    Vector2D(float x = 0.0, float y = 0.0): m_x(x), m_y(y) {}

    float getX() const { return m_x; }
    float getY() const { return m_y; }

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }


    float length() { return sqrt(m_x * m_x + m_y * m_y); }

    Vector2D operator+(const Vector2D& v2) const
    {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }

    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;

        return v1;
    }

    Vector2D operator*(float scalar)
    {
        return Vector2D(m_x * scalar, m_y * scalar);
    }

    Vector2D& operator*=(float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;

        return *this;
    }

    Vector2D operator-(const Vector2D& v2) const
    {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }

    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;

        return v1;
    }

    Vector2D operator/(float scalar)
    {
        return Vector2D(m_x / scalar, m_y / scalar);
    }

    Vector2D& operator/=(float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;

        return *this;
    }    

    void normalize()
    {
        float l = length();
        if (l > 0)
            (*this) *= 1/l;
    }

private:

    float m_x;
    float m_y;
};

#endif

