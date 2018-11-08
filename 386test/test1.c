#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <math.h>
// | sin(x) |
// sin function in mips glibc is fuxking slow so mode it by ourselves
#ifdef __mips
	 #include "sin.h"
	 #define INTEG_FUNC(x)  fabs(qsin(x))
#else
	#define INTEG_FUNC(x)  fabs(sin(x))
#endif
// Prototype timing function
// double clock(void);
int testmain(void)
{
	 // Loop counters and number of interior points
	 unsigned int i, j, N;
	 // Stepsize, independent variable x, and accumulated sum
	 double step, x_i, sum;
	 // Timing variables for evaluation   
	 clock_t start, finish;
	 // Start integral from 
	 double interval_begin = 0.0;
	 // Complete integral at 
	 double interval_end = 2.0 * 3.141592653589793238;
	 // Start timing for the entire application
	 printf("     \n");
	 printf("    Number of    | Computed Integral | \n");
	 printf(" Interior Points |                   | \n");
	 start = clock();
	 for (j=2;j<27;j++)
	 {
		printf("------------------------------------- \n");
		 // Compute the number of (internal rectangles + 1)
		 N =  1 << j;
		 // Compute stepsize for N-1 internal rectangles 
		 step = (interval_end - interval_begin) / N;
		 // Approx. 1/2 area in first rectangle: f(x0) * [step/2] 
		 sum = INTEG_FUNC(interval_begin) * step / 2.0;
		 // Apply midpoint rule:
		 // Given length = f(x), compute the area of the
		 // rectangle of width step
		 // Sum areas of internal rectangle: f(xi + step) * step 
		 for (i=1;i<N;i++)
		 {
				x_i = i * step;
				sum += INTEG_FUNC(x_i) * step;
		 }
		 // Approx. 1/2 area in last rectangle: f(xN) * [step/2] 
		 sum += INTEG_FUNC(interval_end) * step / 2.0;
		 printf(" %10d      |  %14e   | \n", N, sum);
	 }
	 finish = clock();
	 printf("     \n");
	 printf("   Time cost  = %f   s\n", (double)(finish - start)/CLOCKS_PER_SEC);
	 printf("     \n");
	 return 0;
}
