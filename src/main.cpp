#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "point2d.h"
#include "segment2d.h"
#include "polygon2d.h"

#define BL_DEBUG

/**
 * the function allows you to read the boundary values for 
 * a polygon and fill in the transmitted polygon vector
 * @param `file` that contain polygons points2D, `polygons` vector of store polygons2D
 */
void read_lines(std::ifstream& file, std::vector<Polygon2D>* polygons)
{
    // init temp segments storage
    std::vector<Segment2D> polygon;

    /* init read values as float, cause python script
        store value whith .0 */
    float startx, starty, endx, endy;

    // try to read two start values for set polygon triggers
    try
    {
        if (!(file >> startx >> starty))
            throw std::string("error to read values from file");
    } catch (std::string& ex) {
        std::cerr << ex << std::endl;
        return;
    }
    
    // init triggers for check, when polygon end
    float trigx = startx, trigy = starty;

    while(file >> endx >> endy)
    {
        polygon.push_back(Segment2D(Point2D((int)startx, (int)starty), 
                                    Point2D((int)endx, (int)endy)));
        if (trigx == endx && trigy == endy)
        {
            file >> startx >> starty;
            trigx = startx;
            trigy = starty;
            polygons->push_back(Polygon2D(0, polygon));
            polygon.clear();
        }
        else{
            startx = endx;
            starty = endy;
        }
    }
}

void calc_layers(std::vector<Polygon2D>* polygons)
{
    for (auto polygon: *polygons)
    {
        polygon.calc_layer(*polygons);
    #ifdef BL_DEBUG
        std::cout << "layer: "<< polygon.layer() << std::endl;
    #endif
    }
}

int main()
{
    std::ifstream file;
    std::string filepath = "../data/input.txt";
    try
    {
        file.open(filepath);
        if(!file.is_open())
            throw std::string("error to open file: " + filepath);

    } catch(const std::string& ex) {
        std::cerr << ex << std::endl;
        file.close();
        return 0;
    }

    std::vector<Polygon2D> polygons;
    read_lines(file, &polygons);
    
#ifdef BL_DEBUG

    size_t count = 1;
    for (const auto& polygon: polygons)
    {
        std::cout << "#polygon " << count << std::endl;
        for (auto it = polygon.border_begin(); it != polygon.border_end(); it++)
            std::cout << *it << std::endl;
        count++;
    }

#endif

    calc_layers(&polygons);

    file.close();

    return 0;
}
