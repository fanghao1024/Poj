#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;

const int max_n=205;
const int inf=0x3f3f3f3f;   int v,next;


int N,K,cnt,mincost,maxflow;
map<int,int>mii;
int head[max_n<<1],pre[max_n<<1],dist[max_n<<1],num[max_n<<1];
bool vis[max_n<<1];
struct Record{
    int x,y,w;
}record[max_n];
struct Edge{
    int to,nxt;
    int cap,flow;
    int cost;
}edge[(max_n*max_n)<<1];
void init(){
    memset(head,-1,sizeof(head));
    mii.clear();
    cnt=0;
}
void add_edge(int u,int v,int cap,int cost){
    edge[cnt].to=v;
    edge[cnt].cap=cap;
    edge[cnt].cost=cost;
    edge[cnt].flow=0;
    edge[cnt].nxt=head[u];
    head[u]=cnt++;
}
void adde(int u,int v,int cap,int cost){
    add_edge(u,v,cap,cost);
    add_edge(v,u,0,-cost);
}
bool SPFA(int s,int t){
    memset(dist,0x3f,sizeof(dist));
    memset(pre,-1,sizeof(pre));
    memset(vis,0,sizeof(vis));
    queue<int> q;
    dist[s]=0;
    q.push(s);
    vis[s]=1;
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
    mincost=maxflow=0;
    int d;
    while(SPFA(s,t)){
        d=inf;
        for(int i=pre[t];i!=-1;i=pre[edge[i^1].to]){
            d=min(d,edge[i].cap-edge[i].flow);
        }
        for(int i=pre[t];i!=-1;i=pre[edge[i^1].to]){
            edge[i].flow+=d;
            edge[i^1].flow-=d;
        }
        maxflow+=d;
        mincost+=d*dist[t];
    }
    return mincost;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d", &N, &K);
        set<int> si;
        init();
        for (int i = 0; i < N; i++)
        {
            scanf("%d %d %d", &record[i].x, &record[i].y, &record[i].w);
            si.insert(record[i].x);
            si.insert(record[i].y);
        }
        int pos=1;
        for (set<int>::iterator it = si.begin(); it != si.end(); it++)
        {
            mii[*it]=pos++;
        }
        int s=0,t=pos;

        for(int i=0;i<N;i++){
            adde(mii[record[i].x],mii[record[i].y],1,-record[i].w);
        }
        for(int i=1;i<=t;i++) adde(i-1,i,K,0);
        printf("%d\n",-MCMF(s,t));
    }
    
    return 0;
}