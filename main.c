//
//  main.c
//  NelderMeadZJM_C
//
//  Created by Zeno Muscarella  on 1/29/14.
//  Copyright (c) 2014 ZJM. All rights reserved.
//

//#include <stdio.h>
//#include <stdlib.h>
#include "NelderMeadAlg.h"  // header calls stdio and stdlib



// Some interesting functions which test optimization of this sort:
// http://en.wikipedia.org/wiki/Test_functions_for_optimization
//
// Beale's function:  f(x,y) = (1.5 -x +x*y)^2+(2.25-x*y^2)^2+(2.625-x+x*y^3)^2
// with a min of f(3,0.5) = 0
// Booth's function: f(x,y) = (x + 2*y-7)^2 +(2*x+y -5)^2
// with a min of f(1,3) = 0
// Matyas function: f(x,y) = 0.26*(x^2 + y^2) - 0.48*x*y
// with a min of f(0,0) = 0
double function(double x,double y) {
    // Booth's function
    // actual min is at (1,3) with an output of 0
    return (x + 2 * y - 7) * (x + 2 * y - 7) + (2 * x + y - 5) * (2 * x + y - 5);
}

int main(int argc, const char * argv[])
{
    
   // declaring pointer to our function
    double (*fxn)(double, double) = &function;
    
    // Declaring 3 different points.. Our simplex!
    point p0;
    p0.x = 2; p0.y = 2;
    point p1;
    p1.x = 1; p1.y = 1;
    point p2;
    p2.x = 3.0; p2.y = 7.0;
    
    
    printf("\nNELDER MEAD, GO !! ***************************\n");
    // Begining the algorithm by calling the function
    AlgNelderMead(p0, p1, p2, fxn);
    
    return 0;
}

