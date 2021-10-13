#include "segment2d.h"

Segment2D::Segment2D() 
{}
Segment2D::Segment2D(const Segment2D& segment): Segment2D(segment.start(), segment.end()) 
{}
Segment2D::Segment2D(const Point2D& start, const Point2D& end): Segment2D(start.x(), start.y(), end.x(), end.y()) 
{}  
Segment2D::Segment2D(const int x1, const int y1, const int x2, const int y2): _start(x1, y1), _end(x2, y2) 
{}

Point2D Segment2D::start() const 
{
    return _start;
}
void Segment2D::set_start(const int x, const int y)
{
    if (_start.x() == x && _start.y() == y)
        return;
    _start.set_x(x);
    _start.set_y(y);
}
void Segment2D::set_start(const Point2D& start)
{
    _start = start;
}
Point2D Segment2D::end() const 
{
    return _end;
}
void Segment2D::set_end(const int x, const int y) 
{
    if (_end.x() == x && _end.y() == y)
        return;
    _end.set_x(x);
    _end.set_y(y);
}
void Segment2D::set_end(const Point2D& end)
{
    _end = end;
}

Segment2D& Segment2D::operator=(const Segment2D& segment)
{
    if (this == &segment)
        return *this;
    _start = segment.start();
    _end = segment.end();

    return *this;
}
/*bool Segment2D::operator==(const Segment2D& segment)
{
    return _start == segment.start() && _end == segment.end();
}
bool Segment2D::operator!=(const Segment2D& segment)
{
    return !(*this==segment);
}*/

std::ostream& operator<<(std::ostream& out, const Segment2D& segment)
{
    return out << segment.start() << " | " << segment.end();
}