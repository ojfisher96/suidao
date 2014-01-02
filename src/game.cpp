#include <cstdio>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "suidao.hpp"
#include "map.hpp"
#include "content.hpp"

namespace Suidao {

Game::Game() {
    map = Map(10,10);
}

void Game::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
}

void Game::LoadContent() {
    SDL_Surface *loaded_image = IMG_Load("graphics/tiles.png");
    if (loaded_image != NULL) {
        Content::SurfaceSheet = SDL_DisplayFormat(loaded_image);
        SDL_FreeSurface(loaded_image);
    } else {
        fprintf(stderr, "Error: image not loaded.");
        exit(1);
    }
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
