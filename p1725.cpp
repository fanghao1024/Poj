#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2e5+10;
const int inf=0x3f3f3f3f;
int N,L,R;
int val[max_n],q[max_n],dp[max_n];
int main(){
    scanf("%d %d %d",&N,&L,&R);
    for(int i=0;i<=N;i++) scanf("%d",val+i);
    int f=0,r=-1;
    int cur=0;
    memset(dp,-0x3f,sizeof(dp));
    dp[0]=0;
    for(int i=0;i<=N;i++){
        for(;cur<i&&i-cur>=L;cur++){
            while(f<=r&&dp[cur]>=dp[q[r]]) r--;
            q[++r]=cur;
        }
        while(f<=r&&i-q[f]>R) f++;
        if(f<=r) dp[i]=val[i]+dp[q[f]];
    }
    int ans=-inf;
    for(int i=N-R+1;i<=N;i++){
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}
