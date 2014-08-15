#include "lua_api.hpp"
#include "coordinate.hpp"
#include "unit.hpp"

#include <cstdio>
#include <vector>

namespace Suidao {

static Map *map;
static std::vector<Unit> *units;

void InitialiseLuaAPI(lua_State *ls) {
    lua_newtable(ls);

    lua_pushcfunction(ls, &map_get_num_column_segments);
    lua_setfield(ls, -2, "GetNumSegments");
    lua_pushcfunction(ls, &map_get_dimensions);
    lua_setfield(ls, -2, "GetDimensions");
    lua_pushcfunction(ls, &map_get_segment);
    lua_setfield(ls, -2, "GetSegment");

    lua_setglobal(ls, "Map");
    
    lua_pushcfunction(ls, &get_entity);
    lua_setglobal(ls, "GetEntity");
}

void SetLuaAPIObjects(Map *m, std::vector<Unit> *u) {
    map = m;
    units = u;
}

int map_get_num_column_segments(lua_State *ls) {
    int num_column_segments;
    
    if (lua_gettop(ls) >= 2 &&
        lua_isnumber(ls, -1) && lua_isnumber(ls, -2)) {
        int x = lua_tointeger(ls, -2);
        int y = lua_tointeger(ls, -1);
        num_column_segments = map->GetColumn(Coord2<int>(x,y)).GetNumSegments();
    } else {
        // ERROR
        num_column_segments = -1;
    }

    lua_pushinteger(ls, num_column_segments);
    return 1;
}

int map_get_dimensions(lua_State *ls) {
    lua_pushinteger(ls, map->GetDimensions().x);
    lua_pushinteger(ls, map->GetDimensions().y);
    return 2;
}

int map_get_segment(lua_State *ls) {
    if (lua_gettop(ls) >= 3 &&
        lua_isnumber(ls, -1) && lua_isnumber(ls, -2) &&
        lua_isnumber(ls, -3)) {
        
        int x = lua_tointeger(ls, -3);
        int y = lua_tointeger(ls, -2);
        int segment_num = lua_tointeger(ls, -1);

        const Segment& segment =
            map->GetColumn(Coord2<int>(x,y)).GetSegment(segment_num);

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

int get_entity(lua_State *ls) {
    if (lua_gettop(ls) >= 1 && lua_istable(ls, 1)) {
        lua_getfield(ls, 1, "entity_num");
        lua_getfield(ls, 1, "is_building");
        lua_getfield(ls, 1, "player_id");
        
        EntityID eid = EntityID(lua_tointeger(ls, -1),
                                lua_tointeger(ls, -2),
                                lua_tointeger(ls, -3));
        lua_settop(ls, 1);
        
        if (eid.is_building) {
            // TODO: Buildings
        } else {
            units[eid.player_id][eid.entity_num].PushLuaTable(ls);
        }
    } else {
        // ERROR
        lua_newtable(ls);
    }
    
    return 1;
}
    
}