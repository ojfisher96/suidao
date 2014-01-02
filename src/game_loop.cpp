#include "SDL/SDL.h"
#include "suidao.hpp"

namespace Suidao {

Game::Run() {
    Init();
    for (;;) {
        Input();
        Network();
        
        _timer.nextTickStart();
        Update();
        _timer.nextTickEnd();
        
        Draw();
    }
}

int Timestamp::get_tick() {
    return _tick;
}

void Timestamp::nextTickStart() {
    _tick++;
    _lastTickStart = SDL_GetTicks();
}

void nextTickEnd() {
    _lastTickEnd = SDL_GetTicks();
}

unsigned long long timeSinceLastTickStart() {
    return SDL_GetTicks() - _lastTickStart;
}

unsigned long long timeSinceLastTickEnd() {
    return SDL_GetTicks() - _lastTickEnd;
}

}
