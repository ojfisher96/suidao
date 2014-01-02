#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include "SDL/SDL.h"

namespace Suidao {

enum Orientation {
    N, E, S, W,
};
enum TiltStyle {
    FLAT, CORNER_UP, SIDE_UP, V_UP, CORNER_DOWN, V_DOWN, DIAGONAL,
};

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
    int get_num_segments();
    const Segment& get_segment(int segment_num);
    void make_cut(int top, int bottom, TiltType tilt_type=TiltType());
    void bore(int tilt_type);
    Column();
    Column(int height, int rock_type=0);
};

class Map {
    int height, width;
    Column **columns;
public:
    // Test draw function
    void Draw(SDL_Surface *screen);
    Map(int height, int width);
    Map();
    ~Map();
};

}

#endif // MAP_HPP
