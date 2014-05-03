#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include "SDL2/SDL.h"
#include "coordinate.hpp"
#include "content.hpp"


namespace Suidao {

enum Direction {
    N, E, S, W,
};
typedef Direction Orientation;

enum TiltStyle {
    FLAT, CORNER_UP, SIDE_UP, V_UP, CORNER_DOWN, DIAGONAL, // V_DOWN,
};

const int NUM_TILT_STYLES = 6;

struct TiltType {
    Orientation orientation;
    TiltStyle style;
};

typedef int SurfaceType;
typedef int RockType;

struct Segment {
    int top, bottom;
    TiltType tilt_type;
    SurfaceType surface_type;
    explicit Segment(int top=0, int bottom=0,
                     TiltType tilt_type=TiltType(),
                     SurfaceType surface_type=0);
};

class Column {
    RockType rock_type;
    // Given there will be few updates and segments will be few,
    // a sorted vector does fine.
    std::vector<Segment> segments;
public:
    int GetNumSegments();
    const Segment& GetSegment(int segment_num);
    void MakeCut(int top, int bottom, TiltType tilt_type=TiltType());
    void Bore(TiltType tilt_type);
    void Retilt(TiltType tilt_type);
    Column();
    Column(int height, int rock_type=0);
};

namespace {
const int CORNER_HEIGHTS[][4] =
{
    {0,0,0,0},
    {1,0,0,0},
    {1,1,0,0},
    {1,0,1,0},
    {1,1,1,0},
    {2,1,0,1},
};
enum FoundationType { BLOCK, TILT_AWAY, TILT_TOWARDS };
}

class Map {
    int height, width;
    Column **columns;
    void _DrawTile(SDL_Surface *screen, const Content &content,
                   const Segment &segment,
                   int transformed_x, int transformed_y,
                   bool selected);
    void _DrawFoundation(SDL_Surface *screen, const Content &content,
                         const Segment &segment,
                         int transformed_x, int transformed_y);
    void _DrawTopFoundation(SDL_Surface *screen, const Content &content,
                            const Segment &segment,
                            int transformed_x, int transformed_y);
    
    // Returns height of a corner relative to the base of the tile.
    // 'corner' here is relative to the orientation of the tile.
    int _GetCornerHeight(TiltType tilt_type, Direction corner);
    
public:
    // Test draw function
    void Draw(SDL_Surface *screen, const Content& content,
              Coord2<int> position=Coord2<int>(),
              Orientation rotation=N);
    Map(int height, int width);
    Map();
//    ~Map();
};

}

#endif // MAP_HPP
