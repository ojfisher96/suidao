#ifndef LUA_API_HPP
#define LUA_API_HPP

#include "map.hpp"
#include "lua5.2/lua.hpp"

namespace Suidao {

class LuaAPI {
    Map *map;
    int map_get_num_column_segments(lua_State *ls);
    int map_get_dimensions(lua_State *ls);
    int map_get_segment(lua_State *ls);
  public:
    LuaAPI(Map *map, lua_State *ls);
};

}

#endif // LUA_API_HPP
