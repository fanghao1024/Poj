#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<functional>
#include<map>
using namespace std;

const int max_n=105;
const int max_m=1e4+10;
const int inf=0x3f3f3f3f;
typedef pair<int,int> P;

int head[max_n],cnt,dis[max_n],N,M,S;
bool vis[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_m<<1];
void init(){
	memset(head,-1,sizeof(head));
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	cnt=0;
}
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dij(){
	priority_queue<P,vector<P>,greater<P> > q;
	dis[S]=0;
	q.push(make_pair(0,S));
	while(!q.empty()){
		P p=q.top();q.pop();
		int d=p.first;
		int u=p.second;
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to,w=edge[i].w;
			if(!vis[v]&&dis[v]>d+w){
				dis[v]=d+w;
				q.push(make_pair(dis[v],v));
			}
		}
	}
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		if(!N&&!M) break;
		init();
		int x,y,w;
		while(M--){
			scanf("%d %d %d",&x,&y,&w);
			add_edge(x,y,w);
			add_edge(y,x,w);
		}
		S=1;
		dij();
		printf("%d\n",dis[N]);
	}
	return 0;
}
