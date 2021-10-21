#include "polygon2d.h"
#include <iostream>
Polygon2D::Polygon2D() 
{}
Polygon2D::Polygon2D(const Polygon2D& polygon)
:Polygon2D(polygon.layer(), polygon.border()) 
{}
Polygon2D::Polygon2D(const size_t layer, const std::vector<Segment2D>& border)
:_layer(layer), _border(border) 
{}
Polygon2D::Polygon2D(const size_t layer, const std::vector<Segment2D>::iterator& it_begin, 
                                         const std::vector<Segment2D>::iterator& it_end)
                                         :_layer(layer), _border(it_begin, it_end) 
{}
size_t Polygon2D::layer() const
{
    return _layer;
}
void Polygon2D::set_layer(const size_t layer)
{
    if (_layer == layer)
        return;
    _layer = layer;
}
float Polygon2D::scalar_product(const Point2D& first, const Point2D& second)
{
    return (first.x()*second.x() + first.y()*second.y());
}

size_t Polygon2D::calc_intersec(const Segment2D& ray, const Polygon2D& polygon)
{
    size_t count = 0;
    for (auto segment=polygon.border_begin(); segment != polygon.border_end(); segment++)
    {
        float t1 = 0, t2 = 0, t = 0;
        t1+= scalar_product(ray.start()-segment->start(), segment->end()-segment->start())
            *scalar_product(segment->end()-segment->start(), ray.end()-ray.start());

        t1-= scalar_product(ray.start()-segment->start(), ray.end()-ray.start())
            *scalar_product(segment->end()-segment->start(), segment->end()-segment->start());

        t2+= scalar_product(ray.end()-ray.start(), ray.end()-ray.start())
            *scalar_product(segment->end()-segment->start(), segment->end()-segment->start());

        t2-= scalar_product(ray.end()-ray.start(), segment->end()-segment->start())
            *scalar_product(segment->end()-segment->start(), ray.end()-ray.start());
        t = t1/t2;

        float u1 = 0, u2 = 0;
        u1+= scalar_product(ray.start()-segment->start(), segment->end()-segment->start());
        u1+= t*scalar_product(ray.end()-ray.start(), segment->end()-segment->start());
        u2 = scalar_product(segment->end()-segment->start(), segment->end()-segment->start());

        if (t2 != 0 && u2 != 0)
        {
            Segment2D seg(segment->start() + (segment->end() - segment->start())*u1/u2,
                        ray.start() + (ray.end() - ray.start())*t);
            Point2D tmp(seg.end() - seg.start());
            Point2D close_point((seg.end() + seg.start()) / 2);

            if (scalar_product(close_point - ray.start(), ray.end() - ray.start()) > 0 &&
                scalar_product(close_point - ray.end(), ray.start() - ray.end()) > 0 &&
                scalar_product(close_point - segment->start(), segment->end() - segment->start()) > 0 &&
                scalar_product(close_point - segment->end(), segment->start() - segment->end()) > 0)
            {
                if ((scalar_product(tmp, tmp) - 0.001) < 0)
                    count+=1;
            }
        }
    }

    return count;
}

void Polygon2D::calc_layer(const std::vector<Polygon2D>& polygons)
{
    size_t layer = 0;
    for (auto polygon: polygons)
    {
        if (*this != polygon)
        {
            size_t intersec = 0;
            for (auto segment: _border)
            {
                Segment2D ray(Point2D(0, segment.start().y()), segment.start());
                intersec += calc_intersec(ray, polygon);
            }

            std::cout << intersec << std::endl;

            size_t inter_count = 0;
            if (!(intersec % _border.size()))
            {
                inter_count = intersec / _border.size();
                if (!(inter_count % 2))
                    layer+=1;
            }
        }
    }
    this->_layer = layer;
}
std::vector<Segment2D> Polygon2D::border() const
{
    return _border;
}
std::vector<Segment2D>::const_iterator Polygon2D::border_begin() const
{
    return _border.begin();
}
std::vector<Segment2D>::const_iterator Polygon2D::border_end() const 
{
    return _border.end();
}
Segment2D& Polygon2D::border_at(const size_t pos)
{
    return _border.at(pos);
}
Polygon2D& Polygon2D::operator=(const Polygon2D& polygon)
{
    if (this == &polygon)
        return *this;
    _layer = polygon.layer();
    _border = polygon._border;

    return *this;
}
bool Polygon2D::operator==(const Polygon2D& polygon)
{
    return _layer == polygon.layer() && _border == polygon.border();
}
bool Polygon2D::operator!=(const Polygon2D& polygon)
{
    return !(*this == polygon);
}
