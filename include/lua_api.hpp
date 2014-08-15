#ifndef LUA_API_HPP
#define LUA_API_HPP

#include "map.hpp"
#include "unit.hpp"
#include "game_state.hpp"
#include "lua5.2/lua.hpp"

#include <vector>

namespace Suidao {

int map_get_num_column_segments(lua_State *ls);
int map_get_dimensions(lua_State *ls);
int map_get_segment(lua_State *ls);

int get_entity(lua_State *ls);

void InitialiseLuaAPI(lua_State *ls);
void SetLuaAPIObjects(Map *m, std::vector<Unit> *u);
}

#endif // LUA_API_HPP
