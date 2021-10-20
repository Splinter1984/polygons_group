#include "polygon2d.h"
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
/*bool Polygon2D::operator==(const Polygon2D& polygon)
{
    return _layer == polygon.layer() && _border == polygon._border;
}
bool Polygon2D::operator!=(const Polygon2D& polygon)
{
    return !(*this == polygon);
}*/