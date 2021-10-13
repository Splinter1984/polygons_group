#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "point2d.h"
#include "segment2d.h"
#include "polygon2d.h"

void read_lines(std::ifstream& file, std::vector<Polygon2D>* polygons)
{
    Polygon2D *polygon;
    float startx, starty, endx, endy;
    file >> startx >> starty;
    float trigx, trigy;
    trigx = startx;
    trigy = starty;
    while(file >> endx >> endy)
    {
        polygon->_border.push_back(Segment2D(int(startx), int(starty), int(endx), int(endy)));
        if (trigx == endx && trigy == endy)
        {
            file >> startx >> starty;
            trigx = startx;
            trigy = starty;
            polygons->push_back(*polygon);
            polygon = new Polygon2D;
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
        for (const auto& segment: polygon._border)
            std::cout << segment << std::endl;
        count++;
    }
    file.close();

    return 0;
}
