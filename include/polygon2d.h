#pragma once 
#include "segment2d.h"
#define BL_RELEASE

class Polygon2D
{
    private:
        size_t _id;
        size_t _layer;
        std::vector<Segment2D> _border;
        double _perimeter;
        Polygon2D* _parent;

    public:
        Polygon2D();
        Polygon2D(const Polygon2D& polygon);
        Polygon2D(const size_t id, const size_t layer, const std::vector<Segment2D>& border, 
                                const double perimeter = 0.0, const Polygon2D& parent = nullptr);
        Polygon2D(const size_t id, const size_t layer, const std::vector<Segment2D>::iterator& it_begin, 
                    const std::vector<Segment2D>::iterator& it_end, const double perimeter = 0.0, const Polygon2D& parent = nullptr);
        
        size_t layer() const;
        void set_layer(const size_t layer);

        size_t id() const;

        /* the perimeter is a length of border */
        double perimeter() const;
        void set_perimeter(const double perimeter);

        /* the parent polygon is the polygon external to the current */
        Polygon2D* parent() const;
        void set_parent(const Polygon2D& parent);

        /** layer value calculation
         * calculation of the polygon layer based on the analysis 
         * of intersections of rays emitted from each polygon point with other polygons
         * @param `polygons` vector of polygon2D
         */
        void calc_layer(const std::vector<Polygon2D>& polygons);
        
        std::vector<Segment2D>::const_iterator border_begin() const;
        std::vector<Segment2D>::const_iterator border_end() const;
        Segment2D& border_at(const size_t pos);

        std::vector<Segment2D> border() const;
        void set_border(const Segment2D& border);

        Polygon2D& operator=(const Polygon2D& polygon);
        bool operator==(const Polygon2D& polygon);
        bool operator!=(const Polygon2D& polygon);

        friend std::ostream& operator<<(std::ostream& out, const Polygon2D& polygon); 
    
        /** ray entry calculation
         * the method looks count number of intersec ray and all segments in polygon
         * @param `point` 2d point as part of the polygon being tested
         * @param `polygon` 2d polygon to check nesting
         * 
         * @return number of horizontal intersections of the ray from `point` to infinity
         */
        static size_t calc_intersec(const Point2D& point, const Polygon2D& polygon);
    
        /** check that ray intersec with segment
         * the method looks at a "ray" that starts at the spot under test and extends to infinity 
         * towards the right side of the X-axis. for each segment of the polygon, 
         * it checks to see if the ray intersects.
         * @param `point` 2d point as start of ray
         * @param `segment` 2d segment for intersection test
         * 
         * @return if intersection detected return `true` else `false`
         */
        static bool is_intersec(const Point2D& point, const Segment2D& segment);

};
