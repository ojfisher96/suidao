#include "game_state.hpp"

namespace Suidao {

GameState::GameState() {}
GameState::GameState(const Map& m) {
    map = Map(m.GetDimensions());
    map.Update(m);
}

bool GameState::ProcessCommand(Command c) {
    return false; // Stub returning fail each time.
}

void GameState::Update(const GameState& to_copy) {
    
    Tick();
}

void GameState::Tick() {
    
}

const Map& GameState::GetMap() {
    return map;
}

}
