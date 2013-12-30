#ifndef MAP_HPP
#define MAP_HPP
#include <vector>

namespace Suidao {

struct Segment {
    int top, bottom;
    int tilt_type;
    int surface_type;
    explicit Segment(int top=0, int bottom=0,
                     int tilt_type=0,
                     int surface_type=0);
};

class Column {
public:
    int rock_type;
    // Given there will be few updates and segments will be few,
    // a sorted vector does fine.
    std::vector<Segment> segments;
public:
    void make_cut(int top, int bottom, int tilt_type=0);
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
