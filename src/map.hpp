#ifndef MAP_HPP
#define MAP_HPP
#include <vector>

namespace Suidao {

enum TiltDirections {
    NONE = 0,
    N = 1, E = 2, S = 4, W = 8
};
enum TiltAngle {
    FLAT, DOWN, UP
};

struct TiltType {
    TiltDirections direction;
    TiltAngle angle1, angle2;
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
    void make_cut(int top, int bottom, TiltType tilt_type=TiltType());
    void bore(int tilt_type);
    Column();
    Column(int height, int rock_type=0);
};

class Map {
    int height, width;
    Column **columns;
public:
    Map(int height, int width);
    ~Map();
};

}

#endif // MAP_HPP
