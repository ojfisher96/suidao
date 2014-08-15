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

// This represents the ways in which the top of a segment can be tilted.
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

// Represents a contiguous section of terrain in a column
struct Segment {
    int top, bottom;
    TiltType tilt_type;
    SurfaceType surface_type;
    explicit Segment(int top=0, int bottom=0,
                     TiltType tilt_type=TiltType(),
                     SurfaceType surface_type=0);
};

// Represents a column (unit-square prism) which contains
// segmented blocks of land
class Column {
    RockType rock_type;
    // Given there will be few updates and segments will be few,
    // a sorted vector does fine.
    std::vector<Segment> segments; // In order from high to low.
  public:
    int GetNumSegments();
    const Segment& GetSegment(int segment_num);
    void MakeCut(int top, int bottom, TiltType tilt_type=TiltType());
    void Bore(TiltType tilt_type);
    void Retilt(TiltType tilt_type);
    void Update(const Column& to_copy);
    Column();
    Column(int height, int rock_type=0);
};

namespace {
// Heights of each of the corners for each of the tilt styles
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
    Coord2<int> dimensions;
    Column **columns;
    void _DrawTile(SDL_Renderer *renderer, const Content &content,
                   const Segment &segment,
                   int transformed_x, int transformed_y,
                   bool selected) const;
    void _DrawFoundation(SDL_Renderer *renderer, const Content &content,
                         const Segment &segment,
                         int transformed_x, int transformed_y) const;
    void _DrawTopFoundation(SDL_Renderer *renderer, const Content &content,
                            const Segment &segment,
                            int transformed_x, int transformed_y) const;
    
    // Returns height of a corner relative to the base of the tile.
    // 'corner' here is relative to the orientation of the tile.
    int _GetCornerHeight(TiltType tilt_type, Direction corner) const;
    
  public:
    // Draws the entire map
    void Draw(SDL_Renderer *renderer, const Content& content,
              Coord2<int> position=Coord2<int>(),
              Orientation rotation=N) const;
    // Draws a single column
    void DrawColumn(SDL_Renderer *renderer, const Content& content,
                    Coord2<int> column,
                    Coord2<int> position=Coord2<int>(),
                    Orientation rotation=N) const;
    
    // Updates this map with the data from another.
    void Update(const Map& m);

    // Getter functions
    const Coord2<int>& GetDimensions() const;
    Column& GetColumn(Coord2<int> pos);
    
    Map(Coord2<int> dimensions);
    Map();
};

}

#endif // MAP_HPP
