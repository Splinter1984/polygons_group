#include "polygon2d.h"
#include <iostream>

#define BL_RELEASE

#define THRESHOLD 1e-008

Polygon2D::Polygon2D() 
{}
Polygon2D::Polygon2D(const Polygon2D& polygon)
:Polygon2D(polygon.id(), polygon.layer(), polygon.border())
{}
Polygon2D::Polygon2D(const size_t id, const size_t layer, const std::vector<Segment2D>& border)
:_id(id), _layer(layer), _border(border) 
{}
Polygon2D::Polygon2D(const size_t id, const size_t layer, const std::vector<Segment2D>::iterator& it_begin, 
                                         const std::vector<Segment2D>::iterator& it_end)
                                         :_id(id), _layer(layer), _border(it_begin, it_end) 
{}
size_t Polygon2D::layer() const
{
    return _layer;
}
size_t Polygon2D::id() const
{
    return _id;
}
size_t Polygon2D::parent_id() const
{
    return _parent_id;
}
void Polygon2D::set_layer(const size_t layer)
{
    if (_layer == layer)
        return;
    _layer = layer;
}

bool Polygon2D::is_intersec(const Point2D& point, const Segment2D& segment)
{
    /* compute boolean variables to check the 
       intersection of the segment in the y coordinate */
    bool seg_end_bound, seg_start_bound;
    seg_end_bound = segment.end().y() > point.y();
    seg_start_bound = segment.start().y() > point.y();
    
    if (seg_end_bound != seg_start_bound)
    {
        /* calculate the x coordinate of the intersection point */
        long double close_point_x = (point.y() - segment.end().y()) / (long double)(segment.start().y() - segment.end().y())
                             * (segment.start().x() - segment.end().x()) + segment.end().x();
        
        if (point.x() < close_point_x)
            return true;
    }

    return false;
}

size_t Polygon2D::calc_intersec(const Point2D& point, const Polygon2D& polygon)
{
    size_t count = 0;
    
    /* check the entire border of the polygon for intersection with the ray  */
    for (auto segment=polygon.border_begin(); segment != polygon.border_end(); segment++)
    {
        if (is_intersec(point, *segment))
            count++;
    }

    return count;
}

void Polygon2D::calc_layer(const std::vector<Polygon2D>& polygons)
{
    /* initialize start layer as 1 */
    size_t layer = 1;
    for (auto polygon: polygons)
    {
        if (*this != polygon)
        {
            size_t intersec = 0;
            int point_id = 0;
            for (auto segment: _border)
            {
                int intersec_count = calc_intersec(segment.start(), polygon);

                /* if the number of intersections is even, this means that 
                    the ray went out of the segment's field of view to 
                    reach a point on the polygon */
                intersec += (intersec_count % 2 == 0)? 0: intersec_count;
                point_id++;
                
                #ifdef BL_DEBUG
                    std::cout << " polygon: " << this->id() 
                              << "| point: " << point_id 
                              << "| intersec: " <<  intersec_count 
                              << " with polygon " << polygon.id() 
                              << std::endl;
                #endif

            }
            #ifdef BL_DEBUG
                std::cout <<  std::endl;
            #endif
            /* the computation of the parent polygon is needed as additional grouping information */
            if (intersec && polygon.id() > this->parent_id())
                this->_parent_id = polygon.id();
            
            /* the layer grows only if uncovered intersections are detected */
            layer += intersec? 1: 0;
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
std::ostream& operator<<(std::ostream& out, const Polygon2D& polygon)
{
    for (auto it=polygon.border_begin(); it != polygon.border_end(); it++)
        std::cout << *it << std::endl;
    return out;
}
