#pragma once 
#include "segment2d.h"

class Polygon2D
{
    private:
        size_t _id;
        size_t _parent_id = 0;
        size_t _layer;
        std::vector<Segment2D> _border;

    public:
        Polygon2D();
        Polygon2D(const Polygon2D& polygon);
        Polygon2D(const size_t id, const size_t layer, const std::vector<Segment2D>& border);
        Polygon2D(const size_t id, const size_t layer, const std::vector<Segment2D>::iterator& it_begin, 
                                      const std::vector<Segment2D>::iterator& it_end);
        
        size_t layer() const;
        void set_layer(const size_t layer);

        size_t id() const;
        size_t parent_id() const;

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
    
    protected:
        /** ray entry calculation
         * calculation of ray entry into the polygon based 
         * on its intersections with segments
         * @param `ray` segment based on part of polygon and fixed remote point
         * @param `polygon` polygon for calculating ray occurrences
         */
        size_t calc_intersec(const Segment2D& ray, const Polygon2D& polygon);
        /** scalar product for 2D points
         * @param `first`, `second` two 2D points
         */
        double scalar_product(const Point2D& first, const Point2D& second);

};
