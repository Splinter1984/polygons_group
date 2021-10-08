#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <fstream>
#include "point2d.h"
#include "segment2d.h"

std::vector<std::vector<Segment2D>> find_figure2D(const std::vector<Segment2D>& vec)
{
    std::vector<std::vector<Segment2D>> result;
    std::vector<Segment2D> tmpvec(vec);
    while(!tmpvec.empty())
    {
        std::vector<Segment2D> fig;
        Segment2D start_val = *tmpvec.begin();
        auto find_it = tmpvec.begin();
        Segment2D end_val = *tmpvec.begin();
        while(start_val.start() != end_val.end())
        {
            if (!tmpvec.empty())
            {
                tmpvec.erase(find_it);
                fig.push_back(Segment2D(end_val.start(), end_val.end()));    
                find_it = std::find_if(tmpvec.begin(), tmpvec.end(), [&end_val](const Segment2D& item)
                                {return end_val.end() == item.start();});
                end_val = *find_it;
            }else{
                break;
            }
        }
        tmpvec.erase(find_it);
        fig.push_back(Segment2D(end_val.start(), end_val.end()));
        result.push_back(fig);
    }

    return result;
}

void read_lines(std::ifstream& file, std::vector<Segment2D>* vec)
{
    float startx, starty, endx, endy;
    file >> startx >> starty;
    float trigx, trigy;
    trigx = startx;
    trigy = starty;
    while(file >> endx >> endy)
    {
        vec->push_back(Segment2D(startx, starty, endx, endy));
        if (trigx == endx && trigy == endy)
        {
            file >> startx >> starty;
            trigx = startx;
            trigy = starty;
        }
        else{
            startx = endx;
            starty = endy;
        }
    }
}

void write_lines(std::ofstream& outfile, const std::vector<std::vector<Segment2D>>& vec)
{
    for (const auto& item: vec)
    {
        for (const auto& it: item)
            outfile << it.start() << '\n';
        outfile << (item.end()-1)->end() << '\n';
        outfile << '\n';
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

    std::vector<Segment2D> segments;
    read_lines(file, &segments);
    /*for (const auto& item: segments)
        std::cout << item.start() << " | " << item.end() << std::endl;*/
    
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(segments), std::end(segments), rng);
    std::vector<std::vector<Segment2D>> result = find_figure2D(segments);
    size_t count = 1;
    for (const auto& item: result)
    {
        std::cout << "#group " << count << std::endl;
        for (const auto& it: item)
            std::cout << it.start() << " | " << it.end() << std::endl;
        count++;
    }
    file.close();

    std::ofstream outFile;
    std::string outfilepath = "../data/output.txt";
    try
    {
        outFile.open(outfilepath);
        if(!outFile.is_open())
            throw std::string("error to open file: " + outfilepath);

    } catch(const std::string& ex) {
        std::cerr << ex << std::endl;
        outFile.close();
        return 0;
    }
    write_lines(outFile, result);
    outFile.close();

    return 0;
}