#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "coordinate.hpp"
#include "SDL2/SDL.h"

namespace Suidao {

// Each animation is stored in one image as frames stored vertically.
// The height of each frame is stored to calculate the number of frames.
// The width of each texture is derived from the texture
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
