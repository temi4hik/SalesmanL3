from typing import List, Tuple
cimport cython
from libc.stdlib cimport  malloc
from libc.stdint cimport uint32_t

cdef extern from "line.c":
    ctypedef struct Point:
        float x;
        float y;s

    ctypedef struct Line:
        Point *coordinates;
        float *timestamps;

    void line_init(Line *line, Point *coordinates, float *timestamps, uint32_t size)

    Point line_get_position(Line *line, float timestamp, uint32_t size)



cdef class Line_Py:
    cdef Point *coordinates;
    cdef float *timestamps;
    cdef Line line;
    cdef uint32_t size;

    def __init__(self, coordinates: List[Tuple[float, float]], timestamps: List[float]):
        if len(coordinates) != len(timestamps):
            raise ValueError("Coordinates and timestamps must have equal size")

        if timestamps != sorted(timestamps):
            raise ValueError("Timestamps must be a sorted list")

        if len(coordinates) == 0:
            raise ValueError("Points size must not be zero")


        cdef float *times;
        cdef Point *coords;
        cdef uint32_t size = len(timestamps)

        times = <float *>malloc(size * cython.sizeof(float))
        coords = <Point *>malloc(size * cython.sizeof(Point))

        for i in range(size):
            times[i] = timestamps[i]
            coords[i] = Point(coordinates[i][0], coordinates[i][1])

        cdef Line line;

        line_init(&line, coords, times, size)

        self.line = line
        self.coordinates = coords
        self.timestamps = times
        self.size = size


    def get_position_at(self, timestamp: float):
        cdef Point position

        position = line_get_position(&self.line, timestamp, self.size)

        return position
