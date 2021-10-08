#include "segment2d.h"

Point2D Segment2D::start() const 
{
    return _start;
}
void Segment2D::set_start(const float x, const float y) 
{
    _start.set_x(x); 
    _start.set_y(y);
}
Point2D Segment2D::end() const 
{
    return _end;
}
void Segment2D::set_end(const float x, const float y) 
{
    _end.set_x(x); 
    _end.set_y(y);
}
