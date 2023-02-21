#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=12;
const int inf=0x3f3f3f3f;
int g[max_n][max_n],dp[(1<<11)][11];
int N;
void floyd(){
    for(int k=0;k<N;k++){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
    }
}
void solve(){
    memset(dp,0x3f,sizeof(dp));
    dp[(1<<N)-1][0]=0;
    for(int S=(1<<N)-2;S>=0;S--){
        for(int u=0;u<N;u++){
            for(int v=0;v<N;v++){
                if((u!=0&&!(S>>u&1))||g[u][v]==inf) continue;
                if(!(S>>v&1)&&dp[S][u]>dp[S|1<<v][v]+g[u][v]){
                    dp[S][u]=dp[S | 1 << v][v] + g[u][v];
                }
            }
        }
    }
}
int main(){
    while(scanf("%d",&N)&&N){
        N++;
        memset(g,0x3f,sizeof(g));
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                scanf("%d",&g[i][j]);
            }
        }
        floyd();
        solve();
        printf("%d\n",dp[0][0]);
    }
    return 0;
}