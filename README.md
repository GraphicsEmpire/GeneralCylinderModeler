gencylinder
=========================

gencylinder is a modelling application that enables the design of tube shaped objects with arbitrary cross-sections.


Curve Data Example
=========================
```
Number of supplied control points# 7
Number of splines# #control points - 3 = 4

Splines:                     000111222333
                            /  /  /  /  /
Control Points:          0  1  2  3  4  5  6
                         |        |  |  |  |
Spline0:                 0000000000  |  |  |
                            |        |  |  |
Spline1:                    1111111111  |  |
                               |        |  |
Spline2:                       2222222222  |
                                  |        |
Spline3:                          3333333333

Knot distances from each other:
   1-2----3---4--5
   | |    |   |  |
    .1   .4   .3 .2    individual distances
    .1   .5   .8  1   accumulated distances


```
