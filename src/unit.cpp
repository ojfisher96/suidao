#include "unit.hpp"

namespace Suidao {

Unit::Unit() {}

Unit::Unit(int player_id, std::string script) {
    this->player_id = player_id;
    this->script = script;
}
    
}
