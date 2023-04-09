#include <iostream>
using namespace std;
double v[3][3] = {4.5, 150, 200, 6.0, 300, 500, 5.0, 200, 300};
string n[3] = {"Wide Receiver", "Lineman", "Quarterback"};
double a, b, c;
int main()
{

    while (cin>>a>>b>>c && a + b + c)
    {
        bool flag = 0;
        for (int i = 0; i < 3; i++)
        {
            if (a <= v[i][0] && b >= v[i][1] && c >= v[i][2])
            {
                cout << n[i] << " ";
                flag = 1;
            }
        }
        if (!flag)
            printf("No positions");
        printf("\n");
    }
    return 0;
}
