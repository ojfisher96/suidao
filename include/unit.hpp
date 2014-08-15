#ifndef UNIT_HPP
#define UNIT_HPP
#include <string>
#include "coordinate.hpp"

namespace Suidao {

struct UnitDescription {
    int width, length, height;
    int hitpoints;
};

class Unit {
  public:
    int player_id;
    UnitDescription description;
    Coord3<int> position;
    std::string script;
    
    Unit();
    Unit(int player_id, std::string script);
};

}

#endif // UNIT_HPP
