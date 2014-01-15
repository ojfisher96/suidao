#include "map.hpp"
#include "content.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <cmath>
#include <cstdio>

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
                this->columns[x][y].retilt(tilt);
            } else if (y > height/2) {
                this->columns[x][y] = y - height/2 - 1;
                TiltType tilt;
                tilt.style = SIDE_UP;
                tilt.orientation = E;
                this->columns[x][y].retilt(tilt);
            } else {
                this->columns[x][y] = 0;
            }
        }
    }
}

// Test draw function
void Map::Draw(SDL_Surface *screen, Content &content) {
    // Starting at other side is a hack to get draw order correct.
    for (int x = width-1; x >= 0; x--) {
        for (int y = 0; y < height; y++) {
            double transformed_x = (x/sqrt(2.0) + y/sqrt(2.0))
                * 32 * sqrt(2.0);
            double transformed_y = ((-x/sqrt(2.0) + y/sqrt(2.0))/2 + 5)
                * 32 * sqrt(2.0);

            const Segment& cur_segment = columns[x][y].get_segment(0);
            SDL_Rect tile_sheet_fragment;
            SDL_Rect offset;
            tile_sheet_fragment.x =
                    64*cur_segment.tilt_type.orientation;
            tile_sheet_fragment.y =
                    64*cur_segment.tilt_type.style;
            tile_sheet_fragment.w = 64;
            tile_sheet_fragment.h = 64;
            offset.x = (int)transformed_x;
            offset.y = (int)transformed_y - cur_segment.top*16;
            SDL_BlitSurface(
                content.GetGraphic("content/graphics/tiles.png"),
                                   &tile_sheet_fragment,
                                   screen, &offset);
        }
    }
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

void Column::make_cut(int top, int bottom, TiltType tilt_type) {
    // TODO: binary search for segments to delete/trim.
}

void Column::retilt(TiltType tilt_type) {
    this->segments[0].tilt_type = tilt_type;
}

int Column::get_num_segments() {
    return this->segments.size();
}

const Segment& Column::get_segment(int segment_num) {
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
