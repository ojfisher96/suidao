#include <cstdio>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "suidao.hpp"
#include "map.hpp"
#include "content.hpp"

namespace Suidao {

Game::Game() {
    
}

void Game::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    map = Map(10,10);
}

SDL_Surface *Content::SurfaceSheet;

void Game::LoadContent() {
    SDL_Surface *loaded_image = IMG_Load("graphics/tiles.png");
    if (loaded_image != NULL) {
        Content::SurfaceSheet = SDL_DisplayFormat(loaded_image);
        SDL_FreeSurface(loaded_image);
        if (Content::SurfaceSheet != NULL) {
            int color_key = SDL_MapRGB(Content::SurfaceSheet->format,
                                       0, 0, 0xFF);
            SDL_SetColorKey(Content::SurfaceSheet,
                            SDL_SRCCOLORKEY, color_key);
        }
    }
}

void Game::Input() {
    
}

void Game::Network() {

}

void Game::Update() {
    
}

void Game::Draw() {
    map.Draw(screen);
    SDL_Flip(screen);
}

}
