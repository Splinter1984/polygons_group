#pragma once
#include "point2d.h"
#include <vector>

class Segment2D
{
    private:
        Point2D _start;
        Point2D _end;

    public:
        Segment2D();
        Segment2D(const Segment2D& segment);
        Segment2D(const Point2D& start, const Point2D& end);
        Segment2D(const int x1, const int y1, const int x2, const int y2);

        Point2D start() const;
        void set_start(const int x, const int y);
        void set_start(const Point2D& start);
        Point2D end() const;
        void set_end(const int x, const int y);
        void set_end(const Point2D& end);

        Segment2D& operator=(const Segment2D& segment);
        /*bool operator==(const Segment2D& segment);
        bool operator!=(const Segment2D& segment);*/

        friend std::ostream& operator<<(std::ostream& out, const Segment2D& segment); 
};