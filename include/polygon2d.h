#pragma once 
#include "segment2d.h"

class Polygon2D
{
    private:
        size_t _layer;
        std::vector<Segment2D> _border;

    public:
        Polygon2D() {}
        Polygon2D(const std::vector<Segment2D>& border): _border(border) {}
        Polygon2D(std::vector<Segment2D>::iterator it_begin, std::vector<Segment2D>::iterator it_end): _border(it_begin, it_end) {}

        size_t layer() const;
        void set_layer(const size_t layer);
        std::vector<Segment2D> border();
        void set_border(const Segment2D& border);

        Polygon2D& operator=(const Polygon2D& polygon);
        /*bool operator==(const Polygon2D& polygon);
        bool operator!=(const Polygon2D& polygon);*/

};