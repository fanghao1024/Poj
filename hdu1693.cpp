#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=12;
int T,N,M;
ll v,ans;
ll dp[2][1<<12];
void solve(){
    memset(dp,0,sizeof(dp));
    int pre=0,now=1;
    dp[now][0]=1;
    int total=1<<(M+1);
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%lld",&v);
            swap(now,pre);
            memset(dp[now],0,sizeof(dp[now]));
            int j0=1<<j;
            int j1=j0<<1;
            for(int S=0;S<total;S++){
                bool p=S&j0,q=S&j1;
                if(!v){
                    if(!p&&!q) dp[now][S]+=dp[pre][S];
                }else{
                    if(p^q) dp[now][S]+=dp[pre][S];
                    dp[now][S^j0^j1]+=dp[pre][S];
                }
            }
        }
        swap(now,pre);
        memset(dp[now],0,sizeof(dp[now]));
        for(int S=0;S<(total>>1);S++) dp[now][S<<1]+=dp[pre][S];
    }
    ans=dp[now][0];
}
int main(){
    scanf("%d",&T);
    for(int caseNo=1;caseNo<=T;caseNo++){
        scanf("%d %d",&N,&M);
        solve();
        printf("Case %d: There are %lld ways to eat the trees.\n",caseNo,ans);
    }
    return 0;
}