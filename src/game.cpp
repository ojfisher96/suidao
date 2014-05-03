#include <cstdio>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "suidao.hpp"
#include "map.hpp"
#include "content.hpp"
#include "coordinate.hpp"

namespace Suidao {

Game::Game() {
    
}

void Game::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow( "suidao",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    map = Map(10,10);
}

void Game::LoadContent() {
    content.LoadContent("content", screen->format);
}

void Game::Input() {
    
}

void Game::Network() {

}

void Game::Update() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            Exit();
        }
    }
}

void Game::Draw() {
    map.Draw(screen, content, Coord2<int>(0,240));
    SDL_UpdateWindowSurface(window);
}

void Game::CleanUp() {
    SDL_Quit();
}

}
