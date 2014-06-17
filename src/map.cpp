#include "map.hpp"
#include "content.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cmath>
#include <cstdio>
#include <cassert>
#include "coordinate.hpp"

#define TILE_SIZE 64

namespace Suidao {
//
// Map function implementations
//

Map::Map(Coord2<int> dimensions) {
    this->dimensions = dimensions;
    this->columns = new Column*[dimensions.x];
    for (int x = 0; x < dimensions.x; x++) {
        this->columns[x] = new Column[dimensions.y];
        for (int y = 0; y < dimensions.y; y++) {
            // this->columns[x][y] = Column(1);
            if (y < dimensions.y/2) {
                this->columns[x][y] = dimensions.y/2 - y - 1;
                TiltType tilt;
                tilt.style = SIDE_UP;
                tilt.orientation = W;
                this->columns[x][y].Retilt(tilt);
            } else if (y > dimensions.y/2) {
                this->columns[x][y] = y - dimensions.y/2 - 1;
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
void Map::Draw(SDL_Renderer *renderer, const Content &content,
               Coord2<int> position, Orientation rotation) const {
    // Starting at other side is a hack to get draw order correct.
    for (int x = dimensions.x-1; x >= 0; x--) {
        for (int y = 0; y < dimensions.y; y++) {
            DrawColumn(renderer, content, Coord2<int>(x,y),
                       position, rotation);
        }
    }
}

void Map::DrawColumn(SDL_Renderer *renderer, const Content &content,
                     Coord2<int> column,
                     Coord2<int> position, Orientation rotation) const {
    
    int transformed_x = (column.x + column.y) * TILE_SIZE/2 +
                        position.x;
    int transformed_y = ((-column.x + column.y)) * TILE_SIZE/4 +
                        position.y;
    
    // Only draws top segment for now.
    const Segment& cur_segment =
            columns[column.x][column.y].GetSegment(0);
    
    _DrawFoundation(renderer, content, cur_segment,
                    transformed_x, transformed_y);
    
    _DrawTopFoundation(renderer, content, cur_segment,
                       transformed_x, transformed_y);
    
    _DrawTile(renderer, content, cur_segment,
              transformed_x, transformed_y, false);
}

void Map::_DrawTile(SDL_Renderer *renderer, const Content &content,
                    const Segment &segment,
                    int transformed_x, int transformed_y,
                    bool selected) const {
    SDL_Rect tile_sheet_fragment;
    SDL_Rect offset;
    tile_sheet_fragment.x = TILE_SIZE*segment.tilt_type.orientation;
    tile_sheet_fragment.y = TILE_SIZE*segment.tilt_type.style;
    tile_sheet_fragment.w = TILE_SIZE;
    tile_sheet_fragment.h = TILE_SIZE;
    offset.x = transformed_x;
    offset.y = transformed_y - segment.top*TILE_SIZE/4;
    offset.w = TILE_SIZE;
    offset.h = TILE_SIZE;

    if (!selected) {
        tile_sheet_fragment.y += TILE_SIZE * NUM_TILT_STYLES;
    }

    SDL_RenderCopy(renderer, content.GetGraphic("graphics/tiles.png"),
                   &tile_sheet_fragment, &offset);
}

void Map::_DrawFoundation(SDL_Renderer *renderer, const Content &content,
                          const Segment &segment,
                          int transformed_x, int transformed_y) const {
    SDL_Rect tile_sheet_fragment;
    SDL_Rect offset;
    offset.x = transformed_x;
    offset.y = transformed_y - segment.top*TILE_SIZE/4;
    offset.w = TILE_SIZE;
    offset.h = TILE_SIZE;
    tile_sheet_fragment.w = TILE_SIZE;
    tile_sheet_fragment.h = TILE_SIZE;
    for (int z = segment.top; z > segment.bottom; z--) {
        offset.y += 16;
        
        tile_sheet_fragment.x = TILE_SIZE;
        tile_sheet_fragment.y = BLOCK;
        SDL_RenderCopy(renderer, content.GetGraphic("graphics/foundation.png"),
                       &tile_sheet_fragment, &offset);
        
        tile_sheet_fragment.x = 0;
        tile_sheet_fragment.y = BLOCK;
        SDL_RenderCopy(renderer, content.GetGraphic("graphics/foundation.png"),
                       &tile_sheet_fragment, &offset);
    }
}

void Map::_DrawTopFoundation(SDL_Renderer *renderer, const Content &content,
                             const Segment &segment,
                             int transformed_x, int transformed_y) const {
    SDL_Rect tile_sheet_fragment;
    SDL_Rect offset;
    for (int side = 0; side < 2; side++) {
        
        offset.x = transformed_x;
        offset.y = transformed_y - segment.top*TILE_SIZE/4;
        offset.w = TILE_SIZE;
        offset.h = TILE_SIZE;
        tile_sheet_fragment.w = TILE_SIZE;
        tile_sheet_fragment.h = TILE_SIZE;

        // First layer
        if (_GetCornerHeight(segment.tilt_type, S) > 0) {
            if (_GetCornerHeight(segment.tilt_type,
                                 Direction(int(E) + side*2)) > 0) {
                tile_sheet_fragment.x = TILE_SIZE*side;
                tile_sheet_fragment.y = TILE_SIZE*BLOCK;
            } else {
                tile_sheet_fragment.x = TILE_SIZE*side;
                tile_sheet_fragment.y = TILE_SIZE*TILT_TOWARDS;
            }
            SDL_RenderCopy(renderer, content.GetGraphic("graphics/foundation.png"),
                           &tile_sheet_fragment, &offset);
        } else if (_GetCornerHeight(segment.tilt_type,
                                    Direction(int(E) + side*2)) > 0) {
            tile_sheet_fragment.x = TILE_SIZE*side;
            tile_sheet_fragment.y = TILE_SIZE*TILT_AWAY;
            SDL_RenderCopy(renderer, content.GetGraphic("graphics/foundation.png"),
                           &tile_sheet_fragment, &offset);
        }
        
        // Second layer
        offset.y -= TILE_SIZE/4;
        if (_GetCornerHeight(segment.tilt_type, S) == 2) {
            tile_sheet_fragment.x = TILE_SIZE*side;
            tile_sheet_fragment.y = TILE_SIZE*TILT_TOWARDS;
            SDL_RenderCopy(renderer, content.GetGraphic("graphics/foundation.png"),
                           &tile_sheet_fragment, &offset);
        }
        if (_GetCornerHeight(segment.tilt_type,
                             Direction(int(E) + side*2)) == 2) {
            tile_sheet_fragment.x = TILE_SIZE*side;
            tile_sheet_fragment.y = TILE_SIZE*TILT_AWAY;
            SDL_RenderCopy(renderer, content.GetGraphic("graphics/foundation.png"),
                           &tile_sheet_fragment, &offset);
        }
    }
    
}

int Map::_GetCornerHeight(TiltType tilt_type, Direction corner) const {
    return CORNER_HEIGHTS
            [tilt_type.style]
            [((int)corner - (int)tilt_type.orientation + 4) % 4];
}

void Map::Update(const Map& m) {
    assert(m.GetDimensions().x == dimensions.x &&
           m.GetDimensions().y == dimensions.y);
    for (int x = 0; x < dimensions.x; x++) {
        for (int y = 0; y < dimensions.y; y++) {
            columns[x][y].Update(m.columns[x][y]);
        }
    }
}
    
// Default constructor just to appease the compiler
Map::Map() {
    this->dimensions = Coord2<int>(0,0);
    this->columns = 0; // NULL
}

const Coord2<int>& Map::GetDimensions() const {
    return dimensions;
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

void Column::Update(const Column& to_copy) {
    rock_type = to_copy.rock_type;
    segments = to_copy.segments;
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
