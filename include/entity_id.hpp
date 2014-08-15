#ifndef ENTITY_ID_HPP
#define ENTITY_ID_HPP

namespace Suidao {

// Identifies any user-controlled entity in the game.
struct EntityID {
    int player_id;
    bool is_building;
    int entity_num;
    EntityID();
    EntityID(int player_id, bool is_building, int entity_num);
};

}

#endif // ENTITY_ID_HPP
