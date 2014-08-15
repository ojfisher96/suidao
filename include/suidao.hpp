#ifndef SUIDAO_HPP
#define SUIDAO_HPP

#include "map.hpp"
#include "coordinate.hpp"
#include "game_state.hpp"
#include "menu.hpp"
#include "SDL2/SDL.h"

namespace Suidao {

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

// Should be a power of 2 for efficiency
#define GAME_STATE_CACHE_SIZE 256

class GameTimer {
  private:
    int _tick;
    unsigned int _lastTickStart;
    unsigned int _lastTickEnd;
  public:
    int get_tick();
    void nextTickStart();
    void nextTickEnd();
    // Both in milliseconds
    unsigned int timeSinceLastTickStart(); 
    unsigned int timeSinceLastTickEnd();
    GameTimer();
};

class Game {
  private:
    GameTimer _timer;
    
    Map map;
    Content content;
    Coord2<int> map_draw_position;

    Menu menu;

    GameState states[GAME_STATE_CACHE_SIZE];
    
    SDL_Window* window;
    SDL_Renderer* renderer;

    // TODO: make this an array of rows rather than the whole thing.
    SDL_Texture* map_texture;
    
    void Init();
    void LoadContent();
    void MainMenu();
    void Input();
    void Network();
    void Update();
    void Draw();
    void Exit();
    void CleanUp();
  public:
    void Run();
    Game();
};

}

#endif // SUIDAO_HPP
