#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int max_n = 105;
const int max_w = 4e4 + 10;

int v[max_n], w[max_n], m[max_n];
int used[max_w];
int dp[max_w];
int N, W;

int main()
{
    scanf("%d %d", &N, &W);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d%d%d", &v[i], &w[i], &m[i]);
    }
    
    for (int i = 1; i <= N; i++)
    {
        memset(used, 0, sizeof(used));
        for (int j = w[i]; j <= W; j++)
        {
            if (used[j - w[i]] < m[i] && dp[j] < dp[j - w[i]] + v[i])
            {
                dp[j] = dp[j - w[i]] + v[i];
                used[j] = used[j - w[i]] + 1;
            }
        }
         printf("%d:\n",i);
         for(int j=1;j<=W;j++) printf("%d ",dp[j]);
         printf("\n");
    }
    // for(int j=1;j<=W;j++) printf("%d:%d\n",j,used[j]);

    printf("%d\n", dp[W]);
    return 0;
}
