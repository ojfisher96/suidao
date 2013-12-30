#include "map.hpp"

namespace Suidao {
    //
    // Map function implementations
    //

    // Dummy constructor, columns will be initialised to empty values.
    Map::Map(int height, int width) {
        this->height = height;
        this->width = width;
        this->columns = new Column*[width];
        for (int x = 0; x < width; x++) {
            this->columns[x] = new Column[height];
        }
    }
    
    Map::~Map() {
        for (int x = 0; x < width; x++) {
            delete[] this->columns[x];
        }
        delete[] this->columns;
    }

    ///
    // Column function implementations
    //

    // Default constructor just to appease the compiler
    Column::Column() {
        rock_type = "";
        segments = new std::vector<Segment>;
    }

    Column::Column(int height, std::string rock_type="") {
        this->rock_type = rock_type;
        this->segments = new std::vector<Segment>;
        this->segments.push_back(Segment(height));
    }

    Column::make_cut(int top, int bottom, std::string tilt_type="") {
        // TODO: binary search for segments to delete/trim.
    }
    
    //
    // Segment function implementations
    //
    
    explicit Segment::Segment(int top=0, int bottom=0,
                     std::string tilt_type="",
                     std::string surface_type="") {
        this->top = top;
        this->bottom = bottom;
        this->tilt_type = tilt_type;
        this->surface_type = surface_type;
    }
}
