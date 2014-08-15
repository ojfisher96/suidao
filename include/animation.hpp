#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "coordinate.hpp"
#include "SDL2/SDL.h"

namespace Suidao {

class Animation {
    SDL_Texture* texture;
    int height;
    
  public:
    Animation();
    Animation(SDL_Texture* texture, int height);
    
    void Draw(SDL_Renderer *renderer, Coord2<int> position, int frame);
};

}
#endif // ANIMATION_HPP
