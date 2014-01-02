#include "SDL/SDL.h"
#include "suidao.hpp"
#include "map.hpp"

namespace Suidao {

Game::Game() {
    map = Map(10,10);
}

void Game::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
}

void Game::LoadContent() {
    
}

void Game::Input() {
    
}

void Game::Network() {

}

void Game::Update() {
    
}

void Game::Draw() {
    SDL_Flip(screen);
    
}

}
