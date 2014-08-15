#ifndef UNIT_HPP
#define UNIT_HPP
#include <string>
#include "coordinate.hpp"
#include "entity_id.hpp"
#include "map.hpp"

#include "lua5.2/lua.hpp"

namespace Suidao {

// Unit data which usually isn't modified after unit creation
struct UnitDescription {
    int width, length, height;
    int hitpoints;
};

class Unit {
    lua_State *ls;
  public:
    EntityID unit_id;
    UnitDescription description;
    int hitpoints;
    Coord3<int> position;
    // Name of unit (also the name of the lua script for the unit)
    std::string script_name;
    
    Unit();
    Unit(EntityID unit_id, std::string script_name, Content &content);
    void Update(Map *map);
    // Damages the unit, taking into account any special attributes of
    // the unit or the attacker
    int ReceiveDamage(EntityID attacker, int damage);
    // Pushes a description of this unit to a lua state.
    void PushLuaTable(lua_State *push_to);
};

}

#endif // UNIT_HPP
