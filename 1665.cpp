#include <iostream>
#include <cstdio>
using namespace std;
#define PI 3.1415927
int main()
{
    double d, r, t, ansl, ansspd;
    int kase = 1;
    while (scanf("%lf%lf%lf", &d, &r, &t) == 3 && r != 0)
    {
        ansl = PI * d * r / 12 / 5280;
        ansspd = ansl / (t / 3600);
        printf("Trip #%d: %.2lf %.2lf\n", kase++, ansl, ansspd);
    }
    return 0;
}
