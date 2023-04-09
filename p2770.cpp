#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

const int max_n=110;
const int max_m=max_n*max_n;
const int inf=0x3f3f3f3f;

int N,V,cnt,mincost,maxflow;
map<string,int> msi;
int head[max_n<<1],dist[max_n<<1],pre[max_n<<1],vis[max_n<<1];
string str[max_n];
struct Edge{
    int to,nxt;
    int cap,flow;
    int cost;
}edge[(max_m+max_n)<<1];

void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
    msi.clear();
}
void add_edge(int u,int v,int cap,int cost){
    edge[cnt].to=v;
    edge[cnt].cap=cap;
    edge[cnt].flow=0;
    edge[cnt].cost=cost;
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
    q.push(s);
    dist[s]=0;
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
        mincost+=d*dist[t];
        maxflow+=d;
    }
    return maxflow;
}
void print(int s,int t){
    int v;
    vis[s]=1;
    for(int i=head[s];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(!vis[v]&&((edge[i].flow>0&&edge[i].cost<=0)||(edge[i].flow<0&&edge[i].cost>=0))){
            print(v,t);
            if(v<=t) cout<<str[v]<<endl;
        }
    }
}
int main(){
    string str1,str2;
    int s,t;
    cin>>N>>V;
    init();
    for(int i=1;i<=N;i++){
        cin>>str[i];
        msi[str[i]]=i;
        if(i==1||i==N) adde(i,i+N,2,0);
        else adde(i,i+N,1,0);
    }
    for(int i=1;i<=V;i++){
        cin>>str1>>str2;
        int a=msi[str1],b=msi[str2];
        if (a < b)
        {
            if (a == 1 && b == N)
                adde(a + N, b, 2, -1);
            else
                adde(a + N, b, 1, -1);
        }
        else
        {
            if (b == 1 && a == N)
                adde(b + N, a, 2, -1);
            else
                adde(b + N, a, 1, -1);
        }
    }
    s=1,t=2*N;
    if(MCMF(s,t)==2){
        cout<<-mincost<<endl;
        cout<<str[1]<<endl;
        memset(vis,0,sizeof(vis));
        print(1,N);
        cout<<str[1]<<endl;
    }else{
        cout << "No Solution!"<<endl;
    }
    return 0;
}