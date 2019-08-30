//
//  Line.hpp
//  SalesmanL3
//
//  Created by Artem on 30/08/2019.
//  Copyright © 2019 temi4hik. All rights reserved.
//

#ifndef _SALESMANL3_LINE_H_
#define _SALESMANL3_LINE_H_

#include <vector>

using namespace std;

struct Point {
    float x;
    float y;
    
    Point(float x, float y): x(x), y(y) {}
};


class Line {
private:
    vector<Point> coordinates;
    vector<float> timestamps;
public:
    Line() = default;
    Line(vector<Point> coordinates, vector<float> timestamps);
    Line(Point *coordinates, float *timestamps, uint32_t size);
    
    Point get_position(float timestamp);
};

#endif //_SALESMANL3_LINE_H_
