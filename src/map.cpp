#include "map.hpp"
#include "content.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cmath>
#include <cstdio>

#define TILE_SIZE 64

namespace Suidao {
//
// Map function implementations
//

Map::Map(int height, int width) {
    this->height = height;
    this->width = width;
    this->columns = new Column*[width];
    for (int x = 0; x < width; x++) {
        this->columns[x] = new Column[height];
        for (int y = 0; y < height; y++) {
            // this->columns[x][y] = Column(1);
            if (y < height/2) {
                this->columns[x][y] = height/2 - y - 1;
                TiltType tilt;
                tilt.style = SIDE_UP;
                tilt.orientation = W;
                this->columns[x][y].Retilt(tilt);
            } else if (y > height/2) {
                this->columns[x][y] = y - height/2 - 1;
                TiltType tilt;
                tilt.style = SIDE_UP;
                tilt.orientation = E;
                this->columns[x][y].Retilt(tilt);
            } else {
                this->columns[x][y] = 0;
            }
        }
    }
}

// Test draw function
void Map::Draw(SDL_Surface *screen, const Content &content,
               Orientation rotation) {
    // Starting at other side is a hack to get draw order correct.
    for (int x = width-1; x >= 0; x--) {
        for (int y = 0; y < height; y++) {
            int transformed_x = (x + y) * TILE_SIZE/2;
            int transformed_y = ((-x + y) + 15) * TILE_SIZE/4;

            // Only draws top segment for now.
            const Segment& cur_segment = columns[x][y].GetSegment(0);
            _DrawTile(screen, content, cur_segment,
                      transformed_x, transformed_y);
            
            _DrawFoundation(screen, content, cur_segment,
                            transformed_x, transformed_y);

            _DrawTopFoundation(screen, content, cur_segment,
                               transformed_x, transformed_y);
        }
    }
}

void Map::_DrawTile(SDL_Surface *screen, const Content &content,
                    const Segment &segment,
                    int transformed_x, int transformed_y) {
    SDL_Rect tile_sheet_fragment;
    SDL_Rect offset;
    tile_sheet_fragment.x = TILE_SIZE*segment.tilt_type.orientation;
    tile_sheet_fragment.y = TILE_SIZE*segment.tilt_type.style;
    tile_sheet_fragment.w = TILE_SIZE;
    tile_sheet_fragment.h = TILE_SIZE;
    offset.x = transformed_x;
    offset.y = transformed_y - segment.top*TILE_SIZE/4;
    
    SDL_BlitSurface(content.GetGraphic("graphics/tiles.png"),
                    &tile_sheet_fragment, screen, &offset);
}

void Map::_DrawFoundation(SDL_Surface *screen, const Content &content,
                          const Segment &segment,
                          int transformed_x, int transformed_y) {
    SDL_Rect tile_sheet_fragment;
    SDL_Rect offset;
    offset.x = transformed_x;
    offset.y = transformed_y - segment.top*TILE_SIZE/4;
    tile_sheet_fragment.w = TILE_SIZE;
    tile_sheet_fragment.h = TILE_SIZE;
    for (int z = segment.top; z > segment.bottom; z--) {
        offset.y += TILE_SIZE/4;
        tile_sheet_fragment.x = TILE_SIZE;
        tile_sheet_fragment.y = BLOCK;
        SDL_BlitSurface(content.GetGraphic("graphics/foundation.png"),
                        &tile_sheet_fragment, screen, &offset);
        tile_sheet_fragment.x = 0;
        tile_sheet_fragment.y = BLOCK;
        SDL_BlitSurface(content.GetGraphic("graphics/foundation.png"),
                        &tile_sheet_fragment, screen, &offset);
    }
}

void Map::_DrawTopFoundation(SDL_Surface *screen, const Content &content,
                             const Segment &segment,
                             int transformed_x, int transformed_y) {
    SDL_Rect tile_sheet_fragment;
    SDL_Rect offset;
    for (int side = 0; side < 2; side++) {
        offset.x = transformed_x;
        offset.y = transformed_y - segment.top*TILE_SIZE/4;
        tile_sheet_fragment.w = TILE_SIZE;
        tile_sheet_fragment.h = TILE_SIZE;

        // First layer
        if (_GetCornerHeight(segment.tilt_type, S) > 0) {
            if (_GetCornerHeight(segment.tilt_type,
                                 Direction(int(E) + side*2)) > 0) {
                tile_sheet_fragment.x = TILE_SIZE*side;
                tile_sheet_fragment.y = BLOCK;
            } else {
                tile_sheet_fragment.x = TILE_SIZE*side;
                tile_sheet_fragment.y = TILT_TOWARDS;
            }
            SDL_BlitSurface(content.GetGraphic("graphics/foundation.png"),
                            &tile_sheet_fragment, screen, &offset);
        } else if (_GetCornerHeight(segment.tilt_type,
                                    Direction(int(E) + side*2)) > 0) {
            tile_sheet_fragment.x = TILE_SIZE*side;
            tile_sheet_fragment.y = TILT_AWAY;
            SDL_BlitSurface(content.GetGraphic("graphics/foundation.png"),
                            &tile_sheet_fragment, screen, &offset);
        }

        // Second layer
        offset.y -= TILE_SIZE/4;
        if (_GetCornerHeight(segment.tilt_type, S) == 2) {
            tile_sheet_fragment.x = TILE_SIZE*side;
            tile_sheet_fragment.y = TILT_TOWARDS;
            SDL_BlitSurface(content.GetGraphic("graphics/foundation.png"),
                            &tile_sheet_fragment, screen, &offset);
        }
        if (_GetCornerHeight(segment.tilt_type,
                             Direction(int(E) + side*2)) > 0) {
            tile_sheet_fragment.x = TILE_SIZE*side;
            tile_sheet_fragment.y = TILT_AWAY;
            SDL_BlitSurface(content.GetGraphic("graphics/foundation.png"),
                            &tile_sheet_fragment, screen, &offset);
        }
    }
    
}

int Map::_GetCornerHeight(TiltType tilt_type, Direction corner) {
    return CORNER_HEIGHTS
            [tilt_type.style]
            [((int)corner - (int)tilt_type.orientation + 4) % 4];
}
    
// Default constructor just to appease the compiler
Map::Map() {
    this->height = 0;
    this->width = 0;
    this->columns = 0; // NULL
}

/*
Map::~Map() {
    for (int x = 0; x < width; x++) {
        delete[] this->columns[x];
    }
    delete[] this->columns;
}
*/

//
// Column function implementations
//

// Default constructor just to appease the compiler
Column::Column() {
    this->rock_type = 0;
}

Column::Column(int height, RockType rock_type) {
    this->rock_type = rock_type;
    this->segments.push_back(Segment(height));
}

void Column::MakeCut(int top, int bottom, TiltType tilt_type) {
    // TODO: binary search for segments to delete/trim.
}

void Column::Retilt(TiltType tilt_type) {
    this->segments[0].tilt_type = tilt_type;
}

int Column::GetNumSegments() {
    return this->segments.size();
}

const Segment& Column::GetSegment(int segment_num) {
    return this->segments[segment_num];
}

//
// Segment function implementations
//
    
Segment::Segment(int top, int bottom, 
                 TiltType tilt_type, 
                 SurfaceType surface_type) {
    this->top = top;
    this->bottom = bottom;
    this->tilt_type = tilt_type;
    this->surface_type = surface_type;
}
}
