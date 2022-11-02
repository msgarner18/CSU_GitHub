// R2 Recitation
// Author: Chris Wilcox
// Date:   08/29/2018
// Class:  CS270
// Email:  wilcox@cs.colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double input[3];
double output[2];

void computeSphere(double radius, double *addressOfVolume)
{
    // Compute volume
    double result = (4.0 / 3.0) * (3.141593 * radius * radius * radius);

    // Dereference pointer to return result
    *addressOfVolume = result;
}

void computeRectangle(double side1, double side2, double* area)
{
	*area = side1*side2;
}

void computeCircle(double radius, double* area)
{
	*area = radius*radius*3.14159;
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 5) {
        printf("usage: ./R2 double double double double\n");
        return EXIT_FAILURE;
    }

    // Parse arguments
    double sphereRadius = atof(argv[1]);
    double side1 = atof(argv[2]);
    double side2 = atof(argv[3]);
    double radius = atof(argv[4]);
    
    // Local variable
    double volume;
    double circleArea;
    double recArea;
    // Call function
    computeSphere(sphereRadius, &volume);
    computeRectangle(side1, side2, &recArea);
    computeCircle(radius, &circleArea);
    // Print volume
    printf("The volume of a sphere with radius %.5f equals %.5f.\n", sphereRadius, volume);
    printf("the area of a rectangle with sides %.5f and %.5f is %.5f\n",side1, side2, recArea);
    printf("the area of a circle with radius %.5f is %.5f\n", radius, circleArea);

    // Return success
    return EXIT_SUCCESS;
}
