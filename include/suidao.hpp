#ifndef SUIDAO_HPP
#define SUIDAO_HPP

#include "map.hpp"
#include "SDL/SDL.h"

namespace Suidao {

class GameTimer {
  private:
    int _tick;
    unsigned long long _lastTickStart;
    unsigned long long _lastTickEnd;
  public:
    int get_tick();
    void nextTickStart();
    void nextTickEnd();
    // Both in milliseconds
    unsigned long long timeSinceLastTickStart(); 
    unsigned long long timeSinceLastTickEnd();
    GameTimer();
};

class Game {
  private:
    GameTimer _timer;
    
    Map map;
    Content content;
    
    SDL_Surface* screen;
    
    void Init();
    void LoadContent();
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
