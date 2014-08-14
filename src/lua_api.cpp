#include "lua_api.hpp"
#include "coordinate.hpp"

namespace Suidao {

LuaAPI::LuaAPI(Map *map, lua_State *ls) {
    this->map = map;
    // TODO: register functions
}

int LuaAPI::map_get_num_column_segments(lua_State *ls) {
    int num_column_segments;
    
    if (lua_gettop(ls) >= 2 &&
        lua_isnumber(ls, -1) && lua_isnumber(ls, -2)) {
        int x = lua_tointeger(ls, -1);
        int y = lua_tointeger(ls, -2);
        
        num_column_segments = map->GetColumn(Coord2<int>(x,y)).GetNumSegments();
    } else {
        // ERROR
        num_column_segments = -1;
    }

    lua_pushinteger(ls, num_column_segments);
    return 1;
}

int LuaAPI::map_get_dimensions(lua_State *ls) {
    lua_pushinteger(ls, map->GetDimensions().x);
    lua_pushinteger(ls, map->GetDimensions().y);
    return 2;
}

int LuaAPI::map_get_segment(lua_State *ls) {
    if (lua_gettop(ls) >= 3 &&
        lua_isnumber(ls, -1) && lua_isnumber(ls, -2) &&
        lua_isnumber(ls, -3)) {
        
        int x = lua_tointeger(ls, -1);
        int y = lua_tointeger(ls, -2);
        int segment_num = lua_tointeger(ls, -3);

        const Segment& segment = map->GetColumn(Coord2<int>(x,y)).GetSegment(segment_num);

        lua_newtable(ls);
        lua_pushinteger(ls, segment.top);
        lua_setfield(ls, -2, "top");
        lua_pushinteger(ls, segment.bottom);
        lua_setfield(ls, -2, "bottom");
        lua_pushinteger(ls, (int)segment.surface_type);
        lua_setfield(ls, -2, "surface_type");

        lua_newtable(ls);
        for (int i = 0; i < 4; i++) {
            lua_pushinteger(ls, i);
            lua_pushinteger(ls, CORNER_HEIGHTS
                            [segment.tilt_type.style]
                            [i - (int)(segment.tilt_type.orientation + 4) % 4]);
            lua_settable(ls, -3);
        }
        lua_setfield(ls, -2, "corner_heights");
    } else {
        // ERROR
        lua_newtable(ls);
    }
    
    return 1;
}

}
