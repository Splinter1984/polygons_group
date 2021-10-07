#pragma once
#include <iostream>
class Point2D
{
    private:
        float _x;
        float _y;
    
    public:
        Point2D(){}
        Point2D(const float x, const float y): _x(x), _y(y){}
        float x() const;
        void set_x(const float x);
        float y() const ;
        void set_y(const float y);

        friend bool operator==(const Point2D& lv, const Point2D& rv);
        friend bool operator!=(const Point2D& lv, const Point2D& rv);
        friend std::ostream& operator<<(std::ostream& out, const Point2D& val);
};