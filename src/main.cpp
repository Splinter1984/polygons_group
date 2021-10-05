#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

class Segment
{
    public:
        Segment(const float start_x, const float start_y, const float end_x, const float end_y)
        {
            set_start(start_x, start_y);
            set_end(end_x, end_y);
        }
        const std::pair<float, float> start()
        {
            return _start;
        }
        void set_start(const float start_x, const float start_y)
        {
            _start = std::make_pair(start_x, start_y);
        }
        const std::pair<float, float> end()
        {
            return _end;
        }
        void set_end(const float end_x, const float end_y)
        {
            _end = std::make_pair(end_x, end_y);
        }

    private:
        std::pair<float, float> _start;
        std::pair<float, float> _end;
};

void read_lines(std::ifstream& file, std::vector<Segment>* vec)
{
    float startx, starty, endx, endy;
    while(!file.eof())
    {
        file >> startx >> starty >> endx >> endy;
        vec->push_back(Segment(startx, starty, endx, endy));
    }
}

int main()
{
    std::ifstream file;
    std::string filepath = "data/fig.txt";
    try
    {
        file.open(filepath, std::ifstream::ios_base::out | std::ifstream::ios_base::in);
        if(!file.is_open())
            throw std::string("error to open file: " + filepath);
    }
    catch(const std::string& ex)
    {
        std::cerr << ex << std::endl;
        file.close();
        return 0;
    }

    std::vector<Segment> vec;
    read_lines(file, &vec);
    for (auto item: vec)
        std::cout << item.start().first << " " << item.start().second << " | "
                << item.end().first << " " << item.end().second << std::endl;
    

    auto rng = std::default_random_engine {};
    std::shuffle(vec.begin(), vec.end(), rng);
    std::cout << std::endl;
    for (auto item: vec)
    std::cout << item.start().first << " " << item.start().second << " | "
            << item.end().first << " " << item.end().second << std::endl;

    return 0;
}