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

// Keeps track of how long each frame lasts
// and the current tick.
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

    // Default map
    Map map;
    Content content;
    // Position of the view of the world
    Coord2<int> map_draw_position;

    Menu menu;

    // A cache of game states is kept in case a rollback needs to occur
    // (e.g. a command wasn't sent over the network in time)
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
