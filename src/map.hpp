#ifndef MAP_HPP
#define MAP_HPP
#include <string>
#include <vector>

namespace Suidao {

struct Segment {
    int top, bottom;
    std::string tilt_type;
    std::string surface_type;
    explicit Segment(int top=0, int bottom=0,
                     std::string tilt_type="",
                     std::string surface_type="");
};

class Column {
public:
    std::string rock_type;
    // Given there will be few updates and segments will be few,
    // a sorted vector does fine.
    std::vector<Segment> *segments;
public:
    void make_cut(int top, int bottom, std::string tilt_type="");
    void bore(std::string tilt_type);
    Column();
    Column(int height, std::string rock_type="");
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
