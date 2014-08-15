#include <cstdio>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "suidao.hpp"
#include "map.hpp"
#include "content.hpp"
#include "coordinate.hpp"

namespace Suidao {

Game::Game() {
    
}

// Initialise the game
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

    TTF_Init();

    menu.Init();

    // Create original map
    map = Map(Coord2<int>(10,10));
    map_draw_position = Coord2<int>(0,240);

    // Initialise all the game states in the cache
    for (int i = 0; i < GAME_STATE_CACHE_SIZE; i++) {
        states[i] = GameState(map, &content);
    }
}

void Game::LoadContent() {
    content.LoadContent("content", renderer);
}

void Game::MainMenu() {
    SDL_Event event;
    for (;;) {
        SDL_RenderClear(renderer);
        menu.Draw(renderer);
        SDL_RenderPresent(renderer);

        if (!SDL_PollEvent(&event)) continue;
        if (event.type == SDL_QUIT) {
            Exit();
        } else if (event.type == SDL_MOUSEBUTTONDOWN && 
                event.button.button == SDL_BUTTON_LEFT) {
            int clickx = event.button.x, clicky = event.button.y;
            if (menu.boxes["play"].inBox(clickx, clicky)) break;
            else if (menu.boxes["quit"].inBox(clickx, clicky)) {
                Exit();
            } 
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

// Gets input for the game
void Game::Input() {
    // Exit when X pressed or Alt-F4 or whatever.
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

    // Move the view around
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
    // TODO: Networking code
}

void Game::Update() {

    // Test command
    if (_timer.get_tick() == 10) {
        states[_timer.get_tick() % GAME_STATE_CACHE_SIZE]
                .ProcessCommand(Command());
    }

    // Advance to the next state and update
    states[(_timer.get_tick()+1) % GAME_STATE_CACHE_SIZE]
            .Update(states[_timer.get_tick() % GAME_STATE_CACHE_SIZE]);
}

void Game::Draw() {
    SDL_RenderClear(renderer);
    // Draw the map at the current state
    states[_timer.get_tick() % GAME_STATE_CACHE_SIZE]
            .GetMap().Draw(renderer, content, map_draw_position);
    SDL_RenderPresent(renderer);
}

void Game::CleanUp() {
    TTF_Quit();
    SDL_Quit();
}

}
