#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <vector>

template<typename T>
void read_lines(std::ifstream& file, std::vector<std::pair<T, T>>* vec)
{
    T right, left;
    while(!file.eof())
    {
        file >> right >> left;
        vec->push_back(std::make_pair(right, left));
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
    std::vector<std::pair<float, float>> vec;
    read_lines(file, &vec);
    for (const auto& item: vec)
        std::cout<< item.first << "|" << item.second << std::endl;

    return 0;
}