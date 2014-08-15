#ifndef LUA_API_HPP
#define LUA_API_HPP

#include "map.hpp"
#include "lua5.2/lua.hpp"

namespace Suidao {

int map_get_num_column_segments(lua_State *ls);
int map_get_dimensions(lua_State *ls);
int map_get_segment(lua_State *ls);
void InitialiseLuaAPI(Map *m, lua_State *ls);
void SetLuaAPIMap(Map *m);
}

#endif // LUA_API_HPP
