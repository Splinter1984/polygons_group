#pragma once
#include <ostream>

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
        
        Point2D operator+(const Point2D& point);
        Point2D operator-(const Point2D& point);
        Point2D operator*(const int value);
        Point2D operator/(const int value);

        bool operator==(const Point2D& point);
        bool operator!=(const Point2D& point);
        
        friend bool operator==(const Point2D& first, const Point2D& second);
        friend bool operator!=(const Point2D& first, const Point2D& second);
        
        friend std::ostream& operator<<(std::ostream& out, const Point2D& point);
};