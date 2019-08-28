//
// Created by Artem on 2019-08-24.
//

#ifndef _SALESMANC_LINE_H_
#define _SALESMANC_LINE_H_

#include <stdint.h>

typedef struct Point {
    float x;
    float y;
} Point;

typedef struct Line {
    const Point *coordinates;
    const float *timestamps;
} Line;

void line_init(Line *line, const Point *coordinates, const float *timestamps, uint32_t size);

Point line_get_position(const Line *line, float timestamp, uint32_t size);

#endif //_SALESMANC_LINE_H_
