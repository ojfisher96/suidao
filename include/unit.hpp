#ifndef UNIT_HPP
#define UNIT_HPP
#include <string>
#include "coordinate.hpp"
#include "entity_id.hpp"
#include "map.hpp"

#include "lua5.2/lua.hpp"

namespace Suidao {

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
    std::string script_name;
    
    Unit();
    Unit(EntityID unit_id, std::string script_name, Content &content);
    void Update(Map *map);
    int ReceiveDamage(EntityID attacker, int damage);
    void PushLuaTable(lua_State *push_to);
};

}

#endif // UNIT_HPP
