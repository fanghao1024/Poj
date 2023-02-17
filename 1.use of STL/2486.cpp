#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
const int max_k=205;
int N,K,cnt;
int val[max_n],dp[max_n][max_k][2];
int head[max_n];
struct Edge{
    int to,nxt;
}edge[max_n<<1];
void init(){
    memset(dp,0,sizeof(dp));
    memset(head,-1,sizeof(head));
    cnt=0;
}
void add_edge(int x,int y){
    edge[cnt].to=y;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
void dfs(int u,int fa){
    for(int i=0;i<=K;i++) dp[u][i][0]=dp[u][i][1]=val[i];
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa) continue;
        dfs(v,u);
        for(int j=K;j>=1;j--){
            for(int t=1;t<=j;t++){
                dp[u][j][0]=max(dp[u][j][0],dp[v][t-1][0]+dp[u][j-t][1]);
                if(t>=2) dp[u][j][0]=max(dp[u][j][0],dp[v][t-2][1]+dp[u][j-t][0]);
                if(t>=2) dp[u][j][1]=max(dp[u][j][1],dp[v][t-2][1]+dp[u][j-t][1]);
            }
        }
    }
}
int main(){
    int x,y;
    while(scanf("%d %d",&N,&K)!=EOF){
        init();
        for(int i=1;i<=N;i++) scanf("%d",&val[i]);
        for(int i=1;i<N;i++){
            scanf("%d %d",&x,&y);
            add_edge(x,y);
            add_edge(y,x);
        }
        dfs(1,-1);
        printf("~%d\n",max(dp[1][K][0],dp[1][K][1]));
    }
    return 0;
}
