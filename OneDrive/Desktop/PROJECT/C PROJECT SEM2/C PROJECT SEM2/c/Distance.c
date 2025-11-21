#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double calculate(double sLatitude, double sLongitude, double eLatitude, double eLongitude) {
    double radiansOverDegrees = (PI / 180.0);

    double sLatitudeRadians = sLatitude * radiansOverDegrees;
    double sLongitudeRadians = sLongitude * radiansOverDegrees;
    double eLatitudeRadians = eLatitude * radiansOverDegrees;
    double eLongitudeRadians = eLongitude * radiansOverDegrees;

    double dLongitude = eLongitudeRadians - sLongitudeRadians;
    double dLatitude = eLatitudeRadians - sLatitudeRadians;

    double result1 = pow(sin(dLatitude / 2.0), 2.0) +
                     cos(sLatitudeRadians) * cos(eLatitudeRadians) *
                     pow(sin(dLongitude / 2.0), 2.0);

    double result2 = 3956.0 * 2.0 *
                     atan2(sqrt(result1), sqrt(1.0 - result1));

    return result2;
}

int main() {
    double sLatitude = 37.7749;
    double sLongitude = -122.4194;
    double eLatitude = 34.0522;
    double eLongitude = -118.2437;

    double distance = calculate(sLatitude, sLongitude, eLatitude, eLongitude);
    printf("Distance between the two points is: %.2f miles\n", distance);

    return 0;
}