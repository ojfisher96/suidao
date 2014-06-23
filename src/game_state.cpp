#include "game_state.hpp"
#include "coordinate.hpp"

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
    map.Update(to_copy.map);
    Tick();
}

void GameState::Tick() {
    
}

const Map& GameState::GetMap() {
    return map;
}

Command::Command() {}

Command::Command(EntityID commanded, CommandType type,
                 bool target_is_entity, Coord3<int> click) {
    this->commanded = commanded;
    this->type = type;
    this->target_is_entity = target_is_entity;
}

Command::Command(EntityID commanded, CommandType type,
                 bool target_is_entity, EntityID target) {
    this->commanded = commanded;
    this->type = type;
    this->target_is_entity = target_is_entity;
    this->target = target;
}

EntityID::EntityID() {}

EntityID::EntityID(int player_id, bool is_building, int entity_num) {
    this->player_id = player_id;
    this->is_building = is_building;
    this->entity_num = entity_num;
}

}
