#pragma once 
#include "segment2d.h"

class Polygon2D
{
    private:
        size_t _layer;
        std::vector<Segment2D> _border;

    public:
        Polygon2D();
        Polygon2D(const Polygon2D& polygon);
        Polygon2D(const size_t layer, const std::vector<Segment2D>& border);
        Polygon2D(const size_t layer, const std::vector<Segment2D>::iterator& it_begin, 
                                      const std::vector<Segment2D>::iterator& it_end);

        size_t layer() const;
        void set_layer(const size_t layer);
        
        std::vector<Segment2D>::const_iterator border_begin() const;
        std::vector<Segment2D>::const_iterator border_end() const;
        Segment2D& border_at(const size_t pos);

        std::vector<Segment2D> border() const;
        void set_border(const Segment2D& border);

        Polygon2D& operator=(const Polygon2D& polygon);
        /*bool operator==(const Polygon2D& polygon);
        bool operator!=(const Polygon2D& polygon);*/

};