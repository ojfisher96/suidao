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
    window = SDL_CreateWindow("suidao",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    IMG_Init(IMG_INIT_PNG);
    
    map = Map(Coord2<int>(10,10));
    map_draw_position = Coord2<int>(0,240);
    
    for (int i = 0; i < GAME_STATE_CACHE_SIZE; i++) {
        states[i] = GameState(map);
    }
}

void Game::LoadContent() {
    content.LoadContent("content", renderer);
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
    
    const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
    if (keyboard_state[SDL_SCANCODE_UP]) {
        map_draw_position.y += 10;
    }
    if (keyboard_state[SDL_SCANCODE_RIGHT]) {
        map_draw_position.x -= 10;
    }
    if (keyboard_state[SDL_SCANCODE_DOWN]) {
        map_draw_position.y -= 10;
    }
    if (keyboard_state[SDL_SCANCODE_LEFT]) {
        map_draw_position.x += 10;
    }
}

void Game::Network() {
    
}

void Game::Update() {

    if (_timer.get_tick() == 10) {
        states[_timer.get_tick() % GAME_STATE_CACHE_SIZE]
                .ProcessCommand(Command());
    }

    states[(_timer.get_tick()+1) % GAME_STATE_CACHE_SIZE]
            .Update(states[_timer.get_tick() % GAME_STATE_CACHE_SIZE]);
}

void Game::Draw() {
    SDL_RenderClear(renderer);
    states[_timer.get_tick() % GAME_STATE_CACHE_SIZE]
            .GetMap().Draw(renderer, content, map_draw_position);
    SDL_RenderPresent(renderer);
}

void Game::CleanUp() {
    SDL_Quit();
}

}
