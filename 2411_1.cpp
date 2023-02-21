#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=13;
int h,w,now,old;
ll dp[2][1<<11];
void solve(){
    memset(dp,0,sizeof(dp));
    now=0,old=1;
    dp[now][(1<<w)-1]=1;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            swap(now,old);
            memset(dp[now],0,sizeof(dp[now]));
            for (int S = 0; S < (1 << w); S++)
            {
                if (i&&!(S & (1 << j)))
                    dp[now][S | (1 << j)] += dp[old][S]; // 上一行为0
                if ((S & (1 << j)))
                {
                    dp[now][S & ~(1 << j)] += dp[old][S];
                    if (j && !(S & (1 << (j-1))))
                        dp[now][S| (1 << (j-1))] += dp[old][S];
                }
            }
        }
    }
}
int main(){
    while(scanf("%d %d",&h,&w)&&(h+w)){
        if(h<w) swap(h,w);
        solve();
        printf("%lld\n",dp[now][(1<<w)-1]);
    }
    return 0;
}