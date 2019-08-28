//
// Created by Artem on 2019-08-24.
//

#include "line.h"

#include <string.h>
#include <stdlib.h>

void line_init(Line *line, const Point coordinates[], const float timestamps[], uint32_t size) {
    Point *coords = (Point *) malloc(size * sizeof(Point));
    float *times = (float *) malloc(size * sizeof(float));

    memcpy(coords, coordinates, sizeof(Point) * size);
    memcpy(times, timestamps, sizeof(float) * size);

    line->coordinates = coords;
    line->timestamps = times;
}

Point line_get_position(const Line *line, float timestamp, uint32_t size) {
    Point null_point = {};

    if (timestamp > line->timestamps[size - 1]) {
        return null_point;
    }

    int _index = -1;
    for (unsigned int i = 0; i < size; ++i) {
        if (line->timestamps[i] == timestamp) {
            return line->coordinates[i];
        }

        if (line->timestamps[i] > timestamp) {
            _index = i;
            break;
        }
    }

    if (_index == -1) {
        return null_point;
    }

    Point p_0 = line->coordinates[_index - 1];
    Point p_1 = line->coordinates[_index];

    float time_spent = line->timestamps[_index] - line->timestamps[_index - 1];

    float v_x = (p_1.x - p_0.x) / time_spent;
    float v_y = (p_1.y - p_0.y) / time_spent;

    float delta_t = timestamp - line->timestamps[_index - 1];

    float x = p_0.x + v_x * delta_t;
    float y = p_0.y + v_y * delta_t;

    Point result = {x, y};

    return result;
}
