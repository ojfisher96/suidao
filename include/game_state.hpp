#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
#include "map.hpp"
#include "coordinate.hpp"
#include "entity_id.hpp"
#include "unit.hpp"

#include <vector>

namespace Suidao {
    
typedef int CommandType;

struct Command {
    EntityID commanded;
    CommandType type;
    bool target_is_entity;
    union {
        Coord3<int> click;
        EntityID target;
    };
    Command();
    Command(EntityID commanded, CommandType type,
            bool target_is_entity, Coord3<int> click);
    Command(EntityID commanded, CommandType type,
            bool target_is_entity, EntityID target);
};

class GameState {
    Content *content;
    int num_players;
    Map map;
    std::vector<Unit> *units;
    void Tick();
  public:
    GameState();
    GameState(const Map& m, Content *content, int num_players=1);
    
    const Map& GetMap();
    bool ProcessCommand(Command c);
    void Update(const GameState& to_copy);
};

}

#endif // GAME_STATE_HPP
