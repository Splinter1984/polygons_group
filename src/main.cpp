#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "point2d.h"
#include "segment2d.h"
#include "polygon2d.h"

void read_lines(std::ifstream& file, std::vector<Polygon2D>* polygons)
{
    std::vector<Segment2D> polygon;
    Segment2D* segment;
    int startx, starty, endx, endy;
    file >> startx >> starty;
    int trigx, trigy;
    trigx = startx;
    trigy = starty;
    while(file >> endx >> endy)
    {
        segment = new Segment2D(startx, starty, endx, endy);
        polygon.push_back(*segment);
        std::cout << *segment << std::endl;
        std::cout << polygon.back() << std::endl;
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
    
    size_t count = 1;
    for (const auto& polygon: polygons)
    {
        std::cout << "#polygon " << count << std::endl;
        for (auto it = polygon.border_begin(); it != polygon.border_end(); it++)
            std::cout << *it << std::endl;
        count++;
    }
    file.close();

    return 0;
}
