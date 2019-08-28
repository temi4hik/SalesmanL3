from salesman import Line_Py


points = [(0., 0.), (2., 2.), (2, 5), (5, 6), (8, 6), (11, 4), (11, 8), (14, 11)]
times = [0, 2, 5, 9, 15, 20, 26, 33]

line = Line_Py(points, times)

print(line.get_position_at(33))


line = Line_Py([1, 2], [1, 2])


