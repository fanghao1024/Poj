#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=205;

int N,M,cnt;
int dp[max_n][max_n];
int head[max_n],val[max_n];
struct Edge{
    int to,nxt;
}edge[max_n];
void add_edge(int x,int y){
    edge[cnt].to=y;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
void dfs(int u,int m){
    if(m<0) return ;
    dp[u][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        dfs(v,m-1);
        for(int j=m;j>=1;j--){
            for(int k=1;k<j;k++){
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
            }
        }
    }
}
int main(){
    while(scanf("%d %d",&N,&M)&&(N+M)){
        memset(head,-1,sizeof(head));
        int a;
        cnt=0;
        val[0]=0;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=N;i++){
            scanf("%d %d",&a,&val[i]);
            add_edge(a,i);
        }
        M++;
        dfs(0,M);
        printf("%d\n",dp[0][M]);
    }
    return 0;
}