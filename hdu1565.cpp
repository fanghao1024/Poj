#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=22;
int N,now,old,v;
int dp[2][1<<20],ans;
void solve(){
    memset(dp,0,sizeof(dp));
    ans=0;
    now=0,old=1;
    dp[now][0]=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&v);
            swap(now,old);
            for(int S=0;S<(1<<N);S++){
                int newS=S&(~(1<<j));
                dp[now][newS]=max(dp[now][newS],dp[old][S]);
                if(((S&(1<<j))==0)&&(j==0||((S&(1<<(j-1)))==0))){
                    dp[now][S|(1<<j)]=max(dp[now][S|1<<j],dp[old][S]+v);
                }
            }
        }
    }
    for(int S=0;S<(1<<N);S++) ans=max(ans,dp[now][S]);
}
int main(){
    while(scanf("%d",&N)!=EOF){
        solve();
        printf("%d\n",ans);
    }
    return 0;
}