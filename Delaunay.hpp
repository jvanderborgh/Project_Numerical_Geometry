#pragma once

/*
 * This library is for performed delaunay triangulation using an increamental algorithm
 */

#include <algorithm> // useful for std::min
#include <memory>
#include <iostream>

class Point;
class Triangle;

typedef std::shared_ptr<Triangle>  Tptr;
typedef std::tuple<int, int, Tptr> Edge;