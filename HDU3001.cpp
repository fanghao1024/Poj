#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_n=13;
const int inf=0x3f3f3f3f;
int N,M,ans;

int g[max_n][max_n];
int dp[60000][11];
int dig[60000][11];
int tri[12];

void init(){
    tri[0]=0;
    tri[1]=1;
    for(int i=2;i<=11;i++) tri[i]=tri[i-1]*3;
    int up_bound=int(pow(3,10));
    memset(dig,0,sizeof(dig));
    for(int i=0;i<up_bound;i++){
        int t=i;
        for(int j=1;j<=10;j++){
            dig[i][j]=t%3;
            t/=3;
            if(!t) break;
        }
    }
}
void solve(){
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=N;i++){
        dp[tri[i]][i]=0;
    }
    bool flag;
    ans=inf;
    int up_bound = int(pow(3, 10));
    for(int S=0;S<tri[N+1];S++){
        flag=1;
        for(int u=1;u<=N;u++){
            if(dig[S][u]==0){
                flag=0;
                continue;
            }
            for(int v=1;v<=N;v++){
                if(dig[S][v]==0) continue;
                dp[S][u]=min(dp[S][u],dp[S-tri[u]][v]+g[u][v]);
            }
        }
        if(flag){
            for(int i=1;i<=N;i++) ans=min(ans,dp[S][i]);
        }
    }
}
int main(){
    init();
    while(scanf("%d %d",&N,&M)!=EOF){
        memset(g,0x3f,sizeof(g));
        int a,b,c;
        while(M--){
            scanf("%d %d %d",&a,&b,&c);
            g[a][b]=g[b][a]=min(g[a][b],c);
        }
        solve();
        if (ans == inf)
            ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}