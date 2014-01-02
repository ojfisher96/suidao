#ifndef SUIDAO_HPP
#define SUIDAO_HPP

#include "map.hpp"

namespace Suidao {

class Game {
  private:
    GameTimer _timer;
    
    Map map;

    void Init();
    void Input();
    void Network();
    void Update();
    void Draw();
  public:
    void Run();
    Game();
};

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
    Timestamp();
}

}

#endif // SUIDAO_HPP
