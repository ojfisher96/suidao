#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
#include "map.hpp"
#include "coordinate.hpp"
#include "entity_id.hpp"
#include "unit.hpp"

#include <vector>

namespace Suidao {
    
typedef int CommandType;

// A command is a single change which is made to the game state.
// Each command is generated from user input, then fed into the local
// game state as well as other clients on the network if the game is
// multiplayer. This design allows the game to be deterministic and
// means multiplayer can function properly without too much challenge.
struct Command {
    EntityID commanded;
    CommandType type;
    bool target_is_entity;
    // The target of a command can either be an entity (unit or building)
    // or a position on the map.
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

// The game state stores the state of the simulation up to
// a certain point.
class GameState {
    Content *content;
    int num_players;
    Map map;
    std::vector<Unit> *units;
    // Tick steps through the simulation which doesn't involve
    // the processing of a command
    void Tick();
  public:
    GameState();
    GameState(const Map& m, Content *content, int num_players=1);
    
    const Map& GetMap();
    bool ProcessCommand(Command c);
    // Update will copy the given game state then call tick.
    void Update(const GameState& to_copy);
};

}

#endif // GAME_STATE_HPP
