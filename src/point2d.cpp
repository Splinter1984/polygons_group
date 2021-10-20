#include "point2d.h"

Point2D::Point2D()
{}
Point2D::Point2D(const Point2D& point): Point2D(point.x(), point.y())
{}
Point2D::Point2D(const int x, const int y): _x(x), _y(y)
{}

int Point2D::x() const 
{
    return _x;
}
void Point2D::set_x(const int x) 
{
    if (_x == x)
        return;
    _x = x;
}
int Point2D::y() const 
{
    return _y;
}
void Point2D::set_y(const int y) 
{
    if (_y == y)
        return;
    _y = y;
}

Point2D& Point2D::operator=(const Point2D& point)
{
    if (this == &point)
        return *this;
    _x = point.x();
    _y = point.y();
    
    return *this;
}
bool Point2D::operator==(const Point2D& point) 
{
    return _x == point.x() && _y == point.y();
}
bool Point2D::operator!=(const Point2D& point) 
{
    return !(*this == point);
}

std::ostream& operator<<(std::ostream& out, const Point2D& point)
{
    return out << point.x() << " " << point.y();
}
