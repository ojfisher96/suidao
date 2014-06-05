#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
#include "map.hpp"
#include "coordinate.hpp"

namespace Suidao {

typedef int CommandType;

struct EntityID {
    int player_id;
    bool is_building;
    int entity_num;
    EntityID(int player_id, bool is_building, int entity_num) {
        this->player_id = player_id;
        this->is_building = is_building;
        this->entity_num = entity_num;
    }
};

struct Command {
    EntityID commanded;
    CommandType type;
    bool target_is_entity;
    union {
        Coord3<int> click;
        EntityID target;
    };
};

class GameState {
    Map map;
    void Tick();
  public:
    GameState();
    GameState(const Map& m);
    
    const Map& GetMap();
    bool ProcessCommand(Command c);
    void Update(const GameState& to_copy);
};

}

#endif // GAME_STATE_HPP
