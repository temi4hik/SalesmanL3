from typing import List, Tuple
cimport cython
from libcpp.vector cimport vector
from libc.stdint cimport uint32_t

cdef extern from "Line.cpp":
    cdef cppclass Point:
        float x
        float y

        Point(float x, float y) except +
        Point() except +

    cdef cppclass Line:
        vector[Point] coordinates;
        vector[float] timestamps;

        Line() except +
        Line(vector[Point] coordinates, vector[float] timestamps) except +
        Line(Point *coordinates, float *timestamps, uint32_t size) except +

        Point get_position(float timestamp)

cdef class PyPoint:
    cdef Point c_point;

    def __cinit__(self, float x, float y):
        self.c_point = Point(x, y)

    def __str__(self):
        return "x: {}, y: {}".format(self.x, self.y)

    def __repr__(self):
        return "x: {}, y: {}".format(self.x, self.y)

    @property
    def x(self) -> float:
        return self.c_point.x

    @x.setter
    def x(self, val: float):
        self.c_point.x = val

    @property
    def y(self) -> float:
        return self.c_point.y

    @y.setter
    def y(self, val) -> float:
        self.c_point.y = val


cdef class Line_Py:
    cdef vector[Point] coordinates;
    cdef vector[float] timestamps;
    cdef Line line;


    def __init__(self, coordinates: List[Tuple[float, float]], timestamps: List[float]):
        if len(coordinates) != len(timestamps):
            raise ValueError("Coordinates and timestamps must have equal size")

        if timestamps != sorted(timestamps):
            raise ValueError("Timestamps must be a sorted list")

        if len(coordinates) == 0:
            raise ValueError("Points size must not be zero")

        for i in range(len(timestamps)):
            coord = coordinates[i]
            timestamp = timestamps[i]
            p = PyPoint(coord[0], coord[1])

            self.coordinates.push_back(p.c_point)
            self.timestamps.push_back(timestamp)

        self.line = Line(self.coordinates, self.timestamps)


    def get_position_at(self, timestamp: float):
        cdef Point p = self.line.get_position(timestamp)

        point = PyPoint(p.x, p.y)

        return point