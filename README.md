# polygons_group
![](https://img.shields.io/badge/made%20by-splinter1984-blue)	
![](https://img.shields.io/github/languages/code-size/Splinter1984/polygons_group)
### task:
A flat bounded shape is defined by a set of closed polylines that make up its boundary. Polylines do not have common points with each other. It is required to divide the polygonal lines into groups so that each group contains the border of one connected component of the shape.
Polylines are described as sets of points. Each point is like a pair of integers.

### installing:
Clone repository and run build script
```bash
git clone git@github.com:Splinter1984/polygons_group.git
cd polygons_group/scripts/
./compile.sh
```
### running:
you can use ```python``` script to store ```input.txt``` file 
```bash
cd polygons_group/scripts/
python draw_polygons.py
```
run executable file in ```build/``` directory
```bash
cd polygons_group/build/
./polygons_group
```
you can use ```python``` script to visualize ```output.txt``` data
```bash
cd polygons_group/scripts/
python view_polygons.py
```
result of ```python``` build and view scripts
<div align='center'>
  
|input|output|
|:--:|:--:|
![](https://github.com/Splinter1984/polygons_group/blob/master/data/Figure_2.png?raw=true) | ![](https://github.com/Splinter1984/polygons_group/blob/master/data/Figure_1.png?raw=true)
  
</div>

