#include <stdio.h>
#include <math.h>
#define PI 3.1415926535

int main(int argc, char *argv[]) {
    double radius, circumference, area;
    printf("Enter radius of circle:");
    scanf("%lf", &radius);

    circumference = 2*PI*radius;
    area = PI*pow(radius,2);
    printf("Area: %.2lf\n",area);
    printf("Circumference: %.2lf\n", circumference);
    return 0;
}