#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=205;
const int inf=0x3f3f3f3f;
int N,M,cnt,ans;
int head[max_n],pre[max_n];;
bool vis[max_n];
struct Edge{
    int to,nxt;
    int cab,flow;
}edge[max_n<<1];
void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
}
void add_edge(int x,int y,int c){
    edge[cnt].to=y;
    edge[cnt].cab=c;
    edge[cnt].flow=0;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
bool bfs(int s,int t){
    memset(vis,0,sizeof(vis));
    memset(pre,-1,sizeof(pre));
    queue<int> q;
    q.push(s);
    vis[s]=1;
    while(!q.empty()){
        int p=q.front();
        q.pop();
        for(int i=head[p];i!=-1;i=edge[i].nxt){
            int v=edge[i].to;
            if(!vis[v]&&edge[i].cab>edge[i].flow){
                vis[v]=1;
                pre[v]=i;
                if(v==t) return true;
                q.push(v);
            }
        }
    }
    return false;
}
int solve(int s,int t){
    ans=0;
    while(bfs(s,t)){
        int v=t;
        int d=inf;
        while(v!=s){
            int e=pre[v];
            d=min(d,edge[e].cab-edge[e].flow);
            v=edge[e^1].to;
        }
        v=t;
        ans+=d;
        while(v!=s){
            int e=pre[v];
            edge[e].flow+=d;
            edge[e^1].flow-=d;
            v=edge[e^1].to;
        }
    }
    return ans;
}
int main(){
    while(scanf("%d %d",&N,&M)!=EOF){
        init();
        int x,y,c;
        for(int i=0;i<N;i++){
            scanf("%d %d %d",&x,&y,&c);
            add_edge(x,y,c);
            add_edge(y,x,0);
        }
        printf("%d\n",solve(1,M));
    }
    return 0;
}