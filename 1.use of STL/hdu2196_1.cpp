#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=10010;
int N,cnt;
int head[max_n],dp[max_n][3],idx[max_n];
struct Edge{
    int to,w;
    int nxt;
}edge[max_n<<1];
void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
}
void add_edge(int x,int y,int w){
    edge[cnt].to=y;
    edge[cnt].w=w;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
void dfs1(int u,int fa){
    int m1=0,m2=0;
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa) continue;
        dfs1(v,u);
        int c=dp[v][0]+edge[i].w;
        if(c>=m1) m2=m1,m1=c,idx[u]=v;
        else if(c>m2) m2=c;
    }
    dp[u][0]=m1;
    dp[u][1]=m2;
}
void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa) continue;
        if(idx[u]==v) dp[v][2]=max(dp[u][1],dp[u][2])+edge[i].w;
        else dp[v][2]=max(dp[u][0],dp[u][2])+edge[i].w;
        dfs2(v,u);
    }
}
int main(){
    while(scanf("%d",&N)!=EOF){
        init();
        int y,c;
        for(int i=2;i<=N;i++){
            scanf("%d %d",&y,&c);
            add_edge(i,y,c);
            add_edge(y,i,c);
        }
        dfs1(1,0);
        dfs2(1,0);
        for(int i=1;i<=N;i++) printf("%d\n",max(dp[i][0],dp[i][2]));
    }
    return 0;
}