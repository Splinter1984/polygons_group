#include "../include/point2d.h"

float Point2D::x() const 
{
    return _x;
}
void Point2D::set_x(const float x) 
{
    _x = x;
}
float Point2D::y() const 
{
    return _y;
}
void Point2D::set_y(const float y) 
{
    _y = y;
}
bool operator==(const Point2D& lv, const Point2D& rv) 
{
    return lv._x == rv._x && lv._y == rv._y;
}
bool operator!=(const Point2D& lv, const Point2D& rv) 
{
    return !(lv == rv);
}
std::ostream& operator<<(std::ostream& out, const Point2D& val)
{
    return out << val.x() << " " << val.y();
}
