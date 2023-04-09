#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;

typedef pair<int,int> P;
const int max_n=1e4+10;
const int max_m=5e4+10;
const int inf=0x3f3f3f3f;

int N,M,B,cnt;
int F[max_n],temp[max_n],dist[max_n],head[max_n];
bool vis[max_n];
struct Edge{
    int to,nxt;
    int c;
}edge[max_m<<1];
void add_edge(int x,int y,int c){
    edge[cnt].to=y;
    edge[cnt].c=c;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}

bool check(int val){
    memset(vis,0,sizeof(vis));
    memset(dist,0x3f,sizeof(dist));
    for(int i=1;i<=N;i++){
        if(F[i]>val) vis[i]=1;
    }
    if(vis[1]||vis[N]) return false;
    dist[1]=0;
    priority_queue<P,vector<P>,greater<P> > q;
    q.push(make_pair(0,1));
    while(!q.empty()){
        int d=q.top().first;
        int p=q.top().second;
        q.pop();
        if(p==N){
            if(dist[N]<=B) return true;
            else return false;
        }
        if(dist[p]<d) continue;
        if(d>B) return false;
        for(int i=head[p];i!=-1;i=edge[i].nxt){
            int v=edge[i].to;
            if(!vis[v]&&dist[v]>dist[p]+edge[i].c){
                dist[v]=dist[p]+edge[i].c;
                q.push(make_pair(dist[v],v));
            }
        }
    }
    return false;

}
int main(){
    scanf("%d %d %d",&N,&M,&B);
    for(int i=1;i<=N;i++){
        scanf("%d",&F[i]);
        temp[i]=F[i];
    }
    memset(head,-1,sizeof(head));
    cnt=0;
    int x,y,c;
    for(int i=0;i<M;i++){
        scanf("%d %d %d",&x,&y,&c);
        add_edge(x,y,c);
        add_edge(y,x,c);
    }
    sort(temp+1,temp+1+N);
    int l=1,r=N;
    int ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(temp[mid])){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    if(ans==-1) printf("AFK\n");
    else printf("%d\n",temp[ans]);
    return 0;
}
