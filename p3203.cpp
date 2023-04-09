#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int max_n = 2e5 + 10;

int num[max_n], step[max_n], to[max_n], belong[max_n], l[max_n], r[max_n];
int block, tot;

int N, M;
int query(int pos)
{
    int ans = 0;
    while (pos < N)
    {
        ans += step[pos];
        pos = to[pos];
    }
    return ans;
}
void update(int b, int c)
{
    if (b + c >= N)
    {
        to[b] = N;
        step[b] = 1;
    }
    else if (belong[b + c] == belong[b])
    {
        to[b] = to[b + c];
        step[b] = step[b + c] + 1;
    }
    else
    {
        to[b] = b + c;
        step[b] = 1;
    }
    for(int i=b-1;i>=l[belong[b]];i--){
        if(belong[i+num[i]]==belong[i]){
            step[i]=step[i+num[i]]+1;
            to[i]=to[i+num[i]];
        }
    }
}
int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num[i]);
    }
    block = (int)sqrt((double)N);
    tot = N / block;
    if (N % block)
        tot++;
    for (int i = 1; i <= tot; i++)
    {
        l[i] = (i - 1) * block;
        r[i] = i * block - 1;
    }
    r[tot] = N - 1;
    for (int i = 0; i < N; i++)
    {
        belong[i] = i / block + 1;
    }
    belong[N]=tot+1;
    for (int i = tot; i >= 1; i--)
    {
        for (int j = r[i]; j >= l[i]; j--)
        {
            if (j + num[j] >= N)
            {
                to[j] = N;
                step[j] = 1;
                continue;
            }
            if (belong[j + num[j]] == belong[j])
            {
                to[j] = to[j + num[j]];
                step[j] = step[j + num[j]] + 1;
            }
            else
            {
                to[j] = j + num[j];
                step[j] = 1;
            }
        }
    }
    scanf("%d", &M);
    int a, b, c;
    while (M--)
    {
        scanf("%d %d", &a, &b);
        if (a == 1)
        {
            printf("%d\n", query(b));
        }
        else
        {
            scanf("%d", &c);
            num[b]=c;
            update(b, c);
        }
    }
    return 0;
}