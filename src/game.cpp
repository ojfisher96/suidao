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
    map_draw_position = Coord2<int>(0,240);
}

void Game::LoadContent() {
    content.LoadContent("content", screen->format);
}

void Game::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            Exit();
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                Exit();
            }
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]) {
        map_draw_position.y -= 1;
    } else if (state[SDL_SCANCODE_RIGHT]) {
        map_draw_position.x += 1;
    } else if (state[SDL_SCANCODE_DOWN]) {
        map_draw_position.y += 1;
    } else if (state[SDL_SCANCODE_LEFT]) {
        map_draw_position.x -= 1;
    }
}

void Game::Network() {
    
}

void Game::Update() {
    
}

void Game::Draw() {
    map.Draw(screen, content, map_draw_position);
    SDL_UpdateWindowSurface(window);
}

void Game::CleanUp() {
    SDL_Quit();
}

}
