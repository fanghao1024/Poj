#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int max_n = 105;
const int max_w = 4e4 + 10;

int v[max_n], w[max_n], m[max_n];
int dp[max_w];
int N, W;

int main()
{
    scanf("%d %d", &N, &W);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d%d%d", &v[i], &w[i], &m[i]);
    }
    //memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        if(w[i]*m[i]>=W){
            for(int j=w[i];j<=W;j++){
                dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
            }
        }else{
            for(int k=1;m[i]>0;k<<=1){
                int c=min(k,m[i]);
                for(int j=W;j>=w[i]*c;j--){
                    dp[j]=max(dp[j],dp[j-w[i]*c]+v[i]*c);
                }
                m[i]-=k;
            }
        }
    }
    printf("%d\n",dp[W]);
    return 0;
}
