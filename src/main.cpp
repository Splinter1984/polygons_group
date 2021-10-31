#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include "point2d.h"
#include "segment2d.h"
#include "polygon2d.h"

#define BL_RELEASE

/** read points from file 
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
    
    int count_id = 1;
    while(file >> endx >> endy)
    {
        polygon.push_back(Segment2D(Point2D((int)startx, (int)starty), 
                                    Point2D((int)endx, (int)endy)));
        if (trigx == endx && trigy == endy)
        {
            file >> startx >> starty;
            trigx = startx;
            trigy = starty;
            polygons->push_back(Polygon2D(count_id, 0, polygon));
            count_id++;
            polygon.clear();
        }
        else{
            startx = endx;
            starty = endy;
        }
    }
}

/** calculation of the layer for each polygon
 * the function allows you to calculate the layer of each 
 * polygon in the passed array based on the built-in method
 * @param `polygons` vector of store polygons2D
 */
void calc_layers(std::vector<Polygon2D>& polygons)
{
    for (auto polygon=polygons.begin(); polygon!=polygons.end(); polygon++)
    {
        /* selection of a layer for a polygon relative to other polygons
           polygon layer increases in proportion to the number of bounding polygons*/
        polygon->calc_layer(polygons);
        #ifdef BL_DEBUG
            std::cout << "polygon: " << polygon->id() << " layer: "<< polygon->layer() << std::endl;
        #endif
    }
}

/** write polygons to file
 * the function allows you to write the layer 
 * and key points of each polygon to a file
 * @param `file` file to write, `polygons` vector of store polygons2D
 */
void write_polygons(std::ofstream& file,  std::vector<Polygon2D>& polygons)
{
    for (auto polygon: polygons)
    {
        file << "layer:" << polygon.layer() << '\n';
        for (auto segment: polygon.border())
            file << segment.start() << '\n';
        file << polygon.border_begin()->start() << '\n';
        file << '\n';
    }
}

/** fill group polygons id
 * the function distributes polygons into groups depending 
 * on the layer and parent polygon
 * @param `polygons` vector of store polygons2D
 * @param `group` map of group id and vector of polygons inside group
 */
void build_group(const std::vector<Polygon2D>& polygons, std::map<size_t, std::vector<size_t>>& group)
{
    size_t group_num = 0;
    for (const auto& polygon: polygons)
    {
        std::vector<size_t> tmp_group;
        if (polygon.layer() % 2 != 0)
        {
            group_num++;
            tmp_group.push_back(polygon.id());
            for (const auto& item: polygons)
            {
                if (item.parent_id() == polygon.id())
                    tmp_group.push_back(item.id());
            }
            group.insert(std::pair<size_t, std::vector<size_t>>(group_num, tmp_group));
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

    calc_layers(polygons);

#ifdef BL_DEBUG
    std::cout << std::endl;
    for (const auto& polygon: polygons)
    {
        std::cout << "#polygon:" << polygon.id() 
                  << " #parent:" << polygon.parent_id() 
                  << " #layer:" << polygon.layer() << std::endl;
        
        std::cout << polygon;
        std::cout << std::endl;
    }
#endif

    std::map<size_t, std::vector<size_t>> group;
    build_group(polygons, group);
    file.close();

    for (const auto it: group)
    {
        std::cout << "#group: " << it.first << " [ ";
        for (const auto id: it.second)
            std::cout << id << " ";
        std::cout << "]" << std::endl;
    }


    /* the operation of sorting by layers is only necessary 
       for the convenience of drawing polygons in python script */
    std::sort(std::begin(polygons), std::end(polygons), [](Polygon2D lv, Polygon2D rv) 
                                                {return lv.layer() < rv.layer();});

    std::ofstream file_out;
    std::string filepath_out = "../data/output.txt";
    try
    {
        file_out.open(filepath_out);
        if(!file_out.is_open())
            throw std::string("error to open file: " + filepath_out);

    } catch(const std::string& ex) {
        std::cerr << ex << std::endl;
        file_out.close();
        return 0;
    }

    write_polygons(file_out, polygons);

    file_out.close();

    return 0;
}
