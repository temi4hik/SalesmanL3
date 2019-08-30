//
//  Line.cpp
//  SalesmanL3
//
//  Created by Artem on 30/08/2019.
//  Copyright © 2019 temi4hik. All rights reserved.
//

#include "Line.h"


Line::Line(vector<Point> coordinates, vector<float> timestamps) {
    this->coordinates = std::move(coordinates);
    this->timestamps = std::move(timestamps);
}

Line::Line(Point *coordinates, float *timestamps, uint32_t size) {
    this->coordinates.assign(coordinates, coordinates + size);
    this->timestamps.assign(timestamps, timestamps + size);
}

Point Line::get_position(float timestamp) {
    Point null_point = Point(0.0, 0.0);
    
    if (this->coordinates.empty()) {
        return null_point;
    }
    
    if (timestamp > this->timestamps.back()) {
        return null_point;
    }
    
    int _index = -1;
    
    for (int i = 0; i < this->coordinates.size(); ++i) {
        if (this->timestamps[i] == timestamp) {
            return this->coordinates[i];
        }
        
        if (this->timestamps[i] > timestamp) {
            _index = i;
            break;
        }
    }
    
    if (_index == -1) {
        return null_point;
    }
    
    Point p_0 = this->coordinates[_index - 1];
    Point p_1 = this->coordinates[_index];
    
    float time_spent = this->timestamps[_index] - this->timestamps[_index - 1];
    
    float v_x = (p_1.x - p_0.x) / time_spent;
    float v_y = (p_1.y - p_0.y) / time_spent;
    
    float delta_t = timestamp - this->timestamps[_index - 1];
    
    float x = p_0.x + v_x * delta_t;
    float y = p_0.y + v_y * delta_t;
    
    Point result = Point(x, y);
    
    return result;

}
