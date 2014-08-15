#ifndef LUA_API_HPP
#define LUA_API_HPP

#include "map.hpp"
#include "unit.hpp"
#include "game_state.hpp"
#include "lua5.2/lua.hpp"

#include <vector>

// This file provides functions for the lua script interpreter
// which is used for scripting units/buildings and other things.

namespace Suidao {

// Map functions
int map_get_num_column_segments(lua_State *ls);
int map_get_dimensions(lua_State *ls);
int map_get_segment(lua_State *ls);
int map_make_cut(lua_State *ls);

// Entity functions
int get_entity(lua_State *ls);
int attack_entity(lua_State *ls);

// This provides the Lua API to a given lua_State
void InitialiseLuaAPI(lua_State *ls);

// This sets the objects manipulated by the Lua API
// This needs to be done every game state update
void SetLuaAPIObjects(Map *m, std::vector<Unit> *u);
}

#endif // LUA_API_HPP
