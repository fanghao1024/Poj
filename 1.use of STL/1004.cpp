#include <stdio.h>
#include <math.h>
int main()
{
    double dollar[12];
    double sum = 0;
    double average;
    int i;
    for (i = 0; i < 12; i++)
    {
        scanf("%lf", &dollar[i]);
    }
    for (i = 0; i < 12; i++)
    {
        sum = sum + dollar[i];
    }
    average = (float)(sum / 12);
    printf("$%.2f\n", average);
    return 0;
}