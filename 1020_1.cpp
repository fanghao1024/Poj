#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 55
#define M 15

int n, m;
int col[N], s[M];

bool dfs(int mm)
{
    if (mm >= m)
        return true;

    int Min = N, c = 0;
    for (int i = 1; i <= n; i++)
        if (col[i] < Min)
        {
            Min = col[i];
            c = i;
        }

    for (int i = 1; i <= 10; i++)
        if (s[i])
        {
            bool ok = true;
            if (!(c + i - 1 <= n && col[c] + i <= n))
                continue;
            for (int k = c; k <= c + i - 1; k++)
                if (col[k] != col[c])
                {
                    ok = false;
                    break;
                }
            if (!ok)
                continue;

            s[i]--;
            for (int k = c; k <= c + i - 1; k++)
                col[k] += i;
            if (dfs(mm + 1))
                return true;
            s[i]++;
            for (int k = c; k <= c + i - 1; k++)
                col[k] -= i;
        }

    return false;
}

int main()
{
    int cas;
    cin >> cas;
    while (cas--)
    {
        int x, sum = 0;
        cin >> n >> m;
        memset(s, 0, sizeof(s));
        for (int i = 0; i < m; i++)
        {
            cin >> x;
            s[x]++;
            sum += x * x;
        }
        memset(col, 0, sizeof(col));
        if (sum != n * n || !dfs(0))
            cout << "HUTUTU!" << endl;
        else
            cout << "KHOOOOB!" << endl;
    }
    return 0;
}