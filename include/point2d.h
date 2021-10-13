#pragma once
#include <iostream>

class Point2D
{
    private:
        int _x;
        int _y;
    
    public:
        Point2D();
        Point2D(const int x, const int y);
        Point2D(const Point2D& point);

        int x() const;
        void set_x(const int x);
        int y() const ;
        void set_y(const int y);

        Point2D& operator=(const Point2D& point);
        bool operator==(const Point2D& point);
        bool operator!=(const Point2D& point);
        
        friend std::ostream& operator<<(std::ostream& out, const Point2D& point);
};