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

void Game::LoadContent() {
    content.LoadContent("content");
    int color_key = SDL_MapRGB(
        content.GetGraphic("content/graphics/tiles.png")->format,
        0, 0, 0xFF);
    SDL_SetColorKey(content.GetGraphic("content/graphics/tiles.png"),
                    SDL_SRCCOLORKEY, color_key);
}

void Game::Input() {
    
}

void Game::Network() {

}

void Game::Update() {
    
}

void Game::Draw() {
    map.Draw(screen, content);
    SDL_Flip(screen);
}

}
