#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=200010;
int T,N,cnt;
int head[max_n];
int dp[max_n],d[max_n];
int degree[max_n];
void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    memset(d,0,sizeof(d));
    memset(degree,0,sizeof(degree));
}
struct Edge{
    int to,w;
    int nxt;
}edge[max_n<<1];

void add_edge(int x,int y,int w){
    edge[cnt].to=y;
    edge[cnt].w=w;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
void dfs1(int u,int fa){
    d[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa) continue;
        dfs1(v,u);
        if(degree[v]==1) d[u]+=edge[i].w;
        else d[u]+=min(edge[i].w,d[v]);
    }
}
void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa) continue;
        if(degree[u]==1) dp[v]=d[v]+edge[i].w;
        else dp[v]=d[v]+min(edge[i].w,dp[u]-min(d[v],edge[i].w));
        dfs2(v,u);
    }
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        int x,y,c;
        init();
        for(int i=1;i<N;i++){
            scanf("%d %d %d",&x,&y,&c);
            add_edge(x,y,c);
            add_edge(y,x,c);
            degree[x]++;
            degree[y]++;
        }
        dfs1(1,0);
        dp[1]=d[1];
        dfs2(1,0);
        int ans=-1;
        for(int i=1;i<=N;i++) ans=max(ans,dp[i]);
        printf("%d\n",ans);
    }
    return 0;
}