#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1024;
const int max_m=2048;

int head[max_n],cnt,low[max_n],dfn,degree[max_n];
struct Edge{
    int to,nxt;
}edge[max_m<<1];
void init(){
    memset(head,-1,sizeof(head));
    memset(low,0,sizeof(low));
    cnt=0;
}
void add_edge(int x,int y){
    edge[cnt].to=y;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
int N,R;
void dfs(int u,int fa){
    low[u]=++dfn;
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa) continue;
        if(!low[v]) dfs(v,u);
        low[u]=min(low[u],low[v]);
    }
}
int tarjan(){
    memset(degree,0,sizeof(degree));
    for(int i=1;i<=N;i++){
        for(int j=head[i];j!=-1;j=edge[j].nxt){
            int v=edge[j].to;
            if(low[i]!=low[v]) degree[low[i]]++;
        }
    }
    int res=0;
    for(int i=1;i<=N;i++) if(degree[i]==1) res++;
    return res;
}
int main(){
    scanf("%d %d",&N,&R);
    init();
    int x,y;
    while(R--){
        scanf("%d %d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfn=0;
    dfs(1,-1);
    int res=tarjan();
    printf("%d\n",(res+1)>>1);
    return 0;
}