#include "game_state.hpp"
#include "coordinate.hpp"

#include "lua5.2/lua.hpp"
#include "lua_api.hpp"

#include <cstdio>

namespace Suidao {

GameState::GameState() {}
GameState::GameState(const Map& m) {
    map = Map(m.GetDimensions());
    map.Update(m);
}

bool GameState::ProcessCommand(Command c) {
    
    lua_State *ls = luaL_newstate();
    InitialiseLuaAPI(&map, ls);

    // Stub for test of cutting
    map.GetColumn(Coord2<int>(1,9)).MakeCut(2,1);

    if (luaL_dostring(ls, "function foo () return Map.GetSegment(0,0,0).top end")) {
        printf("bleh\n");
        fflush(stdout);
    } else {
        lua_getglobal(ls, "foo");
        lua_call(ls, 0, 1);
        printf("Result: %d\n", lua_tointeger(ls, -1));
    }
    lua_close(ls);
    
    
    return true;
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
