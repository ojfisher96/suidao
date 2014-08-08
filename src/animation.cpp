#include "animation.hpp"

namespace Suidao {
    Animation::Animation() {}
    Animation::Animation(SDL_Texture* texture, int height) {
        this->texture = texture;
        this->height = height;
        // TODO: Check that texture height mod height is 0
    }

    void Animation::Draw(SDL_Renderer *renderer,
                         Coord2<int> position, int frame) {
        int width;
        int total_height;
        SDL_QueryTexture(NULL, NULL, NULL, &total_height, &width);
        
        SDL_Rect tile_sheet_fragment;
        SDL_Rect offset;
        offset.x = position.x;
        offset.y = position.y;
        offset.w = width;
        offset.h = height;
        tile_sheet_fragment.w = width;
        tile_sheet_fragment.h = height;
        tile_sheet_fragment.x = 0;
        tile_sheet_fragment.y = frame * height;
        SDL_RenderCopy(renderer, texture, &tile_sheet_fragment, &offset);
    }
}
