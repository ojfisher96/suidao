#include "game_state.hpp"
#include "coordinate.hpp"

#include "lua5.2/lua.hpp"
#include "lua_api.hpp"

#include <cstdio>

namespace Suidao {

GameState::GameState() {}
GameState::GameState(const Map& m, Content *content,
                     int num_players) {
    map = Map(m.GetDimensions());
    map.Update(m);
    this->num_players = num_players;
    this->content = content;
    this->units = new std::vector<Unit>[num_players];
}

bool GameState::ProcessCommand(Command c) {
    // Test: Add a unit
    units[0].push_back(Unit(EntityID(0, false, 0), "marine", *content));
    
    // Stub for test of cutting (now implemented in marine.lua)
    //map.GetColumn(Coord2<int>(1,9)).MakeCut(2,1);
    
    return true;
}

void GameState::Update(const GameState& to_copy) {
    map.Update(to_copy.map);
    SetLuaAPIObjects(&map, units);
    for (int player = 0; player < num_players; player++) {
        units[player] = to_copy.units[player];
    }
    
    Tick();
}

void GameState::Tick() {
    for (int player = 0; player < num_players; player++) {
        for (int u = 0; u < (int)units[player].size(); u++) {
            units[player][u].Update(&map);
        }
    }
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
