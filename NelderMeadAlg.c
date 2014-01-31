//
//  NelderMeadAlg.c
//  NelderMeadZJM_C
//
//  Created by Zeno Muscarella  on 1/29/14.
//  Copyright (c) 2014 ZJM. All rights reserved.
//

#include "NelderMeadAlg.h"



// implimenting sorting of input points 
point* sortPoints(point p1,
                  point p2,
                  point p3, double(*fxn)(double x, double y) ){
    // assigning input points to an array
    point* array = malloc(sizeof(point)*3);
    array[0] = p1;
    array[1] = p2;
    array[2] = p3;
    // need to sort (using the fact that we know the size of the array apriori
    // using the insertion sorting algorithm
    int i,j;
    point elmPoint;
    double indVal;
    for(i = 0; i < 3; i++) {
        elmPoint = array[i];
        indVal = fxn(array[i].x, array[i].y);
        
        for(j=i; j > 0 && fxn(array[j-1].x,array[j-1].y) > indVal; j--) {
            array[j] = array[j-1];
        }
        array[j] = elmPoint;
    }
    
    return array;
}

// implementing the xOfT (x(t)) function... it returns a point depending on
// reflection, expansion, or contraction. See below for x(t) definition
// cen = .5*(best + med);
// x(t) = cen + t*(cen - worst);
point xOfT(float t, point best, point med, point worst) {
    point stuff;
    stuff.x = 0.5 * (best.x + med.x) + t * ( (0.5*(best.x + med.x)) - worst.x );
    stuff.y = 0.5 * (best.y + med.y) + t * ( (0.5*(best.y + med.y)) - worst.y );

    return stuff;
}


void AlgNelderMead(point p1,
                   point p2,
                   point p3,
                   double(*f)(double x, double y)) {
    
    // Begin by sorting our point array [p1,x2,p3] such that f(p1)<f(p2)<f(p3)
    point *pointArray = sortPoints(p1, p2, p3, f);
    
    point best = pointArray[0];  // declare point with lowest fxn output
    point med = pointArray[1];
    point worst = pointArray[2]; // declare point with highest fxn output
    
    int i = 0;
    
    while( ( (f(worst.x, worst.y) - f(best.x, best.y)) > 0.00005 ) && (i<20) ){
        
        // Wish to print each point after each iteration and after sorting occurs
        printf("\n Iteration: %d",i);
        printf("\n The best point is (%.4f,%.4f) with output: %f \n",
               best. x,best.y, f(best.x,best.y));
        printf("\n The 2nd best point is (%.4f,%.4f) with output: %f \n",
               med.x, med.y, f(med.x,med.y));
        printf("\n The worst point is (%.4f,%.4f) with output: %f \n",
               worst.x, worst.y, f(worst.x, worst.y));
        
        // The Algorithm begins with a reflection check to produce a better point than worst.
        // if the reflection is better than the med but greater than the best, then
        // the worst is set to the reflection
        point ref = xOfT(1, best, med, worst); // reflection point is x(1)
        
        if( ( f(best.x,best.y)<= f(ref.x, ref.y) ) && (f(ref.x, ref.y) <f(med.x, med.y) )){
            worst = ref;
            pointArray = sortPoints(best, med, worst, f);
            best = pointArray[0];
            med = pointArray[1];
            worst = pointArray[2];
            i++;
            continue;
        }
        
        // If the above if statement fails, then we need to try an expansion with respect to the refleciton.
        // Check to see reflection is better than the best in which case we check if the expansion is better
        // than the reflection else the worst is set to the reflection.
        if( f(ref.x,ref.y) < f(best.x,best.y) ){
            point expan = xOfT(2, best, med, worst); // expansion point is x(2)
            if( f(expan.x, expan.y) < f(ref.x,ref.y) ){
                worst = expan;
                pointArray = sortPoints(best, med, worst, f);
                best = pointArray[0];
                med = pointArray[1];
                worst = pointArray[2];
                i++;
                continue;
            } else {
                worst = ref;
                pointArray = sortPoints(best, med, worst, f);
                best = pointArray[0];
                med = pointArray[1];
                worst = pointArray[2];
                i++;
                continue;
            }
        }
        
        // If the reflection isn't better than the best then, we try an outside contraction.
        // If the reflection is better than the worst but greater than the med then we
        // check if the outside contraction is better than the reflection if so, the worst is set to
        // the outside contraction else we shrink the simplex.
        if( (f(med.x, med.y) <= f(ref.x, ref.y) )&&( f(ref.x,ref.y) < f(worst.x, worst.y) ) ) {
            point outCont = xOfT(0.5, best, med, worst); // outside contraction point is x(1/2)
            if( f(outCont.x, outCont.y) <= f(ref.x,ref.y) ) {
                worst = outCont;
                pointArray = sortPoints(best, med, worst, f);
                best = pointArray[0];
                med = pointArray[1];
                worst = pointArray[2];
                i++;
                continue;
            } else {
                // Shrinking Simplex
                med.x = best.x - 0.5 * ( best.x - med.x );
                med.y = best.y - 0.5 * ( best.y - med.y );
                worst.x = best.x - 0.5 * (best.x - worst.x );
                worst.y = best.y - 0.5 * (best.y - worst.y );
                pointArray = sortPoints(best, med, worst, f);
                best = pointArray[0];
                med = pointArray[1];
                worst = pointArray[2];
                i++;
                continue;
            }
        }
        // If the reflection isn't the above then we try an inside contraction. Thus if the reflection
        // is greater than the worst, then we check if the inside contraction is better then the worst.
        // If so, the worst is set to the inside contraction else we need to shrink the simplex.
        if( f(ref.x, ref.y) >= f(worst.x, worst.y) ){
            point inCont = xOfT(-0.5, best, med, worst);
            if( f(inCont.x, inCont.y) < f(worst.x,worst.y) ) {
                worst = inCont; // inside contration point is x(-1/2)
                pointArray = sortPoints(best, med, worst, f);
                best = pointArray[0];
                med = pointArray[1];
                worst = pointArray[2];
                i++;
                
            } else {
                // Shrinking Simplex
                med.x = best.x - 0.5 * ( best.x - med.x );
                med.y = best.y - 0.5 * ( best.y - med.y );
                worst.x = best.x - 0.5 * (best.x - worst.x );
                worst.y = best.y - 0.5 * (best.y - worst.y );
                pointArray = sortPoints(best, med, worst, f);
                best = pointArray[0];
                med = pointArray[1];
                worst = pointArray[2];
                i++;
                continue;
            }
        }

    }// end while loop
    
    
}
