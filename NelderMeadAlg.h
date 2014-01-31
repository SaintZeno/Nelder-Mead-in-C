//
//  NelderMeadAlg.h
//  NelderMeadZJM_C
//
//  Created by Zeno Muscarella  on 1/29/14.
//  Copyright (c) 2014 ZJM. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#ifndef NelderMeadZJM_C_NelderMeadAlg_h
#define NelderMeadZJM_C_NelderMeadAlg_h

// declaring point typedef struct (ie just a point (x,y) in the form of a struct)
typedef struct {
    double x;
    double y;
} point;


// declaring sorting of our points (returns an array of best to worst point)
point* sortPoints(point p1,
               point p2,
               point p3, double(*fxn)(double x, double y) );


// declaring xOfT function for the nelder algorithm
point xOfT(float t, point best, point med, point worst);


// declaring nelder mead algorithm, note that it's a void function
void AlgNelderMead(point p1,
                  point p2,
                  point p3,
                  double(*fxn)(double x, double y));

#endif
