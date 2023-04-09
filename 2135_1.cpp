#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=1024;
const int max_m=2e4+10;
const int inf=0x3f3f3f3f;

int head[max_n],dist[max_n],pre[max_n];
bool vis[max_n];
int N,M,cnt;
struct Edge{
    int to,nxt;
    int cap,flow;
    int cost;
}edge[max_m<<1];

void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
}

void add_edge(int x,int y,int c,int cost){
    edge[cnt].to=y;
    edge[cnt].cap=c;
    edge[cnt].flow=0;
    edge[cnt].cost=cost;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
void adde(int x,int y,int c,int cost){
    add_edge(x,y,c,cost);
    add_edge(y,x,0,-cost);
}
bool SPFA(int s,int t){
    memset(dist,0x3f,sizeof(dist));
    memset(pre,-1,sizeof(pre));
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(s);
    vis[s]=1;
    dist[s]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].nxt){
            int v=edge[i].to;
            if(edge[i].cap>edge[i].flow&&dist[v]>dist[u]+edge[i].cost){
                dist[v]=dist[u]+edge[i].cost;
                pre[v]=i;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    return pre[t]!=-1;
}
int MCMF(int s,int t){
    int mincost=0,d;
    while(SPFA(s,t)){
        d=inf;
        for(int i=pre[t];i!=-1;i=pre[edge[i^1].to]){
            d=min(d,edge[i].cap-edge[i].flow);
        }
        for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to])
        {
            edge[i].flow+=d;
            edge[i^1].flow-=d;
        }
        mincost+=d*dist[t];
    }
    return mincost;
}
int main(){
    scanf("%d %d",&N,&M);
    init();
    int s=0,t=N+1;
    adde(s,1,2,0);
    int x,y,c;
    for(int i=1;i<=M;i++){
        scanf("%d %d %d",&x,&y,&c);
        adde(x,y,1,c);
        adde(y,x,1,c);
    }
    adde(N,t,2,0);
    printf("%d\n",MCMF(s,t));
    return 0;
}