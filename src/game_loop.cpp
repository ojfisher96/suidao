#include "SDL2/SDL.h"
#include "suidao.hpp"

namespace Suidao {

void Game::Run() {
    Init();
    LoadContent();
    for (;;) {
        Input();
        Network();
        
        _timer.nextTickStart();
        Update();
        _timer.nextTickEnd();
        
        Draw();
    }
}

void Game::Exit() {
    CleanUp();
    exit(0);
}

GameTimer::GameTimer() {
    _tick = 0;
    _lastTickStart = 0;
    _lastTickEnd = 0;
}

int GameTimer::get_tick() {
    return _tick;
}

void GameTimer::nextTickStart() {
    _tick++;
    _lastTickStart = SDL_GetTicks();
}

void GameTimer::nextTickEnd() {
    _lastTickEnd = SDL_GetTicks();
}

unsigned int GameTimer::timeSinceLastTickStart() {
    return SDL_GetTicks() - _lastTickStart;
}

unsigned int GameTimer::timeSinceLastTickEnd() {
    return SDL_GetTicks() - _lastTickEnd;
}

}
