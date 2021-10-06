#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

class Point2D
{
    private:
        float _x;
        float _y;
    
    public:
        Point2D(){}
        Point2D(const float x, const float y): _x(x), _y(y){}
        float x() const;
        void set_x(const float x);
        float y() const ;
        void set_y(const float y);

        friend bool operator==(const Point2D& lv, const Point2D& rv);
        friend bool operator!=(const Point2D& lv, const Point2D& rv);
};

float Point2D::x() const {return _x;}
void Point2D::set_x(const float x) {_x = x;}
float Point2D::y() const {return _y;}
void Point2D::set_y(const float y) {_y = y;}
bool operator==(const Point2D& lv, const Point2D& rv) {return lv._x == rv._x && lv._y == rv._y;}
bool operator!=(const Point2D& lv, const Point2D& rv) {return !(lv == rv);}

class Segment2D
{
    private:
        Point2D _start;
        Point2D _end;

    public:
        Segment2D() {}
        Segment2D(const Point2D& start, const Point2D& end): _start(start.x(), start.y()), _end(end.x(), end.y()){}  
        Segment2D(const float x1, const float y1, const float x2, const float y2): _start(x1, y1), _end(x2, y2){}
        Point2D start() const;
        void set_start(const float x, const float y);
        Point2D end() const;
        void set_end(const float x, const float y);
};

Point2D Segment2D::start() const {return _start;}
void Segment2D::set_start(const float x, const float y) {_start.set_x(x); _start.set_y(y);}
Point2D Segment2D::end() const {return _end;}
void Segment2D::set_end(const float x, const float y) {_end.set_x(x); _end.set_y(y);}

class Figure2D
{
    private:
        std::vector<Segment2D> _segments;

    public:
        Figure2D(){}
        void append_segment(const Segment2D& segment);
        std::vector<Segment2D> get_segments() const;
        int size() const;
        
};

void Figure2D::append_segment(const Segment2D& segment)
{
    _segments.push_back(segment);
}
std::vector<Segment2D> Figure2D::get_segments() const 
{
    return _segments;
}
int Figure2D::size() const
{
    return _segments.size();
}

std::vector<Figure2D> find_figure2D(const std::vector<Segment2D>& vec)
{
    std::vector<Figure2D> result;
    std::vector<Segment2D> tmpvec = vec;
    while(!tmpvec.empty())
    {
        Figure2D fig;
        auto key = tmpvec.begin();
        auto value = tmpvec.begin()+1;
        while(key->start() != value->end())
        {
            fig.append_segment(*value);
            tmpvec.erase(value);
            value = std::find_if(tmpvec.begin(), tmpvec.end(), [&value](Segment2D& item)
                                {return value->end() == item.start();});
        }
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

int main()
{
    std::ifstream file;
    std::string filepath = "data/fig.txt";
    try
    {
        file.open(filepath, std::ifstream::ios_base::out | 
                std::ifstream::ios_base::in);
        if(!file.is_open())
            throw std::string("error to open file: " + filepath);

    } catch(const std::string& ex) {
        std::cerr << ex << std::endl;
        file.close();
        return 0;
    }

    std::vector<Segment2D> segments;
    read_lines(file, &segments);
    for (const auto& item: segments)
        std::cout << item.start().x() << " "
                << item.start().y() << " | "
                << item.end().x() << " "
                << item.end().y() << std::endl;
    std::vector<Figure2D> result = find_figure2D(segments);
    for (const auto& item: result)
    {
        std::cout << "group#1" << std::endl;
        for (const auto& it: item.get_segments())
            std::cout << it.start().x() << " "
                    << it.start().y() << " | "
                    << it.end().x() << " "
                    << it.end().y() << std::endl;
    }

    return 0;
}