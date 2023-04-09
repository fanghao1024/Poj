#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=1e5+10;
const int max_m=4e5+10;
const int inf=0x3f3f3f3f;
int s,t,T,N,M,cnt;
int head[max_n],dep[max_n],g[max_n],now[max_n],pre[max_n];
struct Edge{
    int to,nxt;
    int cab,flow;
}edge[max_m];
void add_edge(int x,int y,int c){
    edge[cnt].to=y;
    edge[cnt].cab=c;
    edge[cnt].flow=0;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
void adde(int x,int y,int c){
    add_edge(x,y,c);
    add_edge(y,x,0);
}
void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
}
void bfs(){
    memset(dep,0,sizeof(dep));
    memset(g,0,sizeof(g));
    dep[t]=1;
    queue<int> q;
    q.push(t);
    while(!q.empty()){
        int u=q.front();
        g[dep[u]]++;
        q.pop();
        for(int i=head[u];i!=-1;i=edge[i].nxt){
            int v=edge[i].to;
            if(!dep[v]){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
}

int agument(){
    int d=inf;
    int u=t;
    while(u!=s){
        int e=pre[u];
        d=min(d,edge[e].cab-edge[e].flow);
        u=edge[e^1].to; 
    }
    u=t;
    while(u!=s){
        int e=pre[u];
        edge[e].flow+=d;
        edge[e^1].flow-=d;
        u=edge[e^1].to;
    }
    return d;
}

int isap(int s,int t,int n){
    int maxflow=0;
    bfs();
    int u=s;
    memcpy(now,head,sizeof(head));
    while(dep[s]<=n){
        if(u==t){
            maxflow+=agument();
            u=s;
        }
        
        bool ok=0;
        for (int i = now[u]; i != -1; i = edge[i].nxt)
        {
            int v=edge[i].to;
            if(dep[v]==dep[u]-1&&edge[i].cab&&edge[i].cab>edge[i].flow){
                ok=1;
                pre[v]=i;
                now[u]=i;
                u=v;
                break;
            }
        }
        if(!ok){
            //if(--g[dep[u]]==0) break;
            int mind=n+5;
            for(int i=head[u];i!=-1;i=edge[i].nxt){
                int v=edge[i].to;
                if(edge[i].cab>edge[i].flow&&dep[v]<mind){
                    mind=dep[v];
                    
                }
                
            }
            g[dep[u]]--;
            if(g[dep[u]]==0) break;
            dep[u]=mind+1;
            g[dep[u]]++;
            now[u]=head[u];
            if(u!=s) u=edge[pre[u]^1].to;
        }
    } 
    return maxflow;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&N,&M);
        int Ma=-inf,Mi=inf;
        int x,y,c;
        for(int i=1;i<=N;i++){
            scanf("%d %d",&x,&y);
            if(x<Mi) Mi=x,s=i;
            if(x>Ma) Ma=x,t=i;
        }
        init();
        for(int i=1;i<=M;i++){
            scanf("%d %d %d",&x,&y,&c);
            adde(x,y,c);
            adde(y,x,c);
        }
        
        printf("%d\n",isap(s,t,N));
        //5 2 1 4 3 0
        //for(int i=1;i<=N;i++) printf("%d ",dep[i]);
    }
    return 0;
}
