# broken_lines
### task:
A flat bounded shape is defined by a set of closed polylines that make up its boundary. Polylines do not have common points with each other. It is required to divide the polygonal lines into groups so that each group contains the border of one connected component of the shape.
Polylines are described as sets of points. Each point is like a pair of integers.

### setup:
Clone repository and run build script
```bash
git clone git@github.com:Splinter1984/broken_lines.git
cd broken_lines/scripts/
./compile.sh
```
you can use ```python``` script to store ```input.txt``` file 
```bash
cd broken_lines/scripts/
python buildLines.py
```
run executable file in ```build/``` directory
```bash
cd broken_lines/build/
./broken_lines
```
you can use ```python``` script to visualize ```output.txt``` data
```bash
cd broken_lines/scripts/
python viewLines.py
```
result of ```python``` view script

![](https://github.com/Splinter1984/broken_lines/blob/broken_linesv2.0/data/Figure_1.png?raw=true)
