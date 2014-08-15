#include "unit.hpp"
#include "content.hpp"
#include "lua_api.hpp"


namespace Suidao {

Unit::Unit() {}

Unit::Unit(EntityID unit_id, std::string script_name, Content &content) {
    this->unit_id = unit_id;
    this->script_name = script_name;
    ls = luaL_newstate();
    luaL_openlibs(ls);
    InitialiseLuaAPI(ls);
    luaL_dostring(ls, content.GetScript("units/" + script_name + ".lua").c_str());
}

void Unit::Update(Map *map) {
    lua_getglobal(ls, "update");
    lua_call(ls, 0, 0);
}

int Unit::ReceiveDamage(EntityID attacker, int damage) {
    lua_getglobal(ls, "attacked");
    // TODO: call the function
    lua_newtable(ls);
    lua_pushinteger(ls, attacker.player_id);
    lua_setfield(ls, -2, "player_id");
    lua_pushboolean(ls, attacker.is_building);
    lua_setfield(ls, -2, "is_building");
    lua_pushinteger(ls, attacker.entity_num);
    lua_setfield(ls, -2, "entity_num");
    lua_call(ls, 2, 1);
    int damage_taken = lua_tointeger(ls, -1);
    hitpoints -= damage_taken;
    return damage_taken;
}

// Pushes a Lua table representing the current state of the unit
// to the stack of a lua_State
void Unit::PushLuaTable(lua_State *push_to) {
    // Create a table to hold a description
    // of the current state of this unit.
    lua_newtable(push_to);

    // Push values to table
    lua_pushstring(push_to, this->script_name.c_str());
    lua_setfield(push_to, -2, "script_name");
    lua_pushinteger(push_to, this->hitpoints);
    lua_setfield(push_to, -2, "hitpoints");
    
    // Adding unit description detaipush_to to table
    lua_pushinteger(push_to, this->description.width);
    lua_setfield(push_to, -2, "width");
    lua_pushinteger(push_to, this->description.length);
    lua_setfield(push_to, -2, "length");
    lua_pushinteger(push_to, this->description.height);
    lua_setfield(push_to, -2, "height");
    lua_pushinteger(push_to, this->description.hitpoints);
    lua_setfield(push_to, -2, "total_hitpoints");

    // Table representing entity id
    lua_newtable(push_to);
    lua_pushinteger(push_to, this->unit_id.player_id);
    lua_setfield(push_to, -2, "player_id");
    lua_pushboolean(push_to, this->unit_id.is_building);
    lua_setfield(push_to, -2, "is_building");
    lua_pushinteger(push_to, this->unit_id.entity_num);
    lua_setfield(push_to, -2, "entity_num");
    
    // Push to unit description table
    lua_setfield(push_to, -2, "entity_id");
}

}
