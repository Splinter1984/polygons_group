#pragma once
#include "point2d.h"
#include <vector>

class Segment2D
{
    private:
        Point2D _start;
        Point2D _end;

    public:
        Segment2D() {}
        Segment2D(const Point2D& start, const Point2D& end): _start(start.x(), start.y()), _end(end.x(), end.y()){}  
        Segment2D(const float x1, const float y1, const float x2, const float y2): _start(x1, y1), _end(x2, y2){}
        Point2D start() const;
        void set_start(const float x, const float y);
        Point2D end() const;
        void set_end(const float x, const float y);
};