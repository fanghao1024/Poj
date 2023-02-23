#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=105;
const int inf=0x3f3f3f3f;

int n,np,nc,m,cnt;
int head[max_n],d[max_n];
struct Edge{
	int to,nxt;
	int cab,flow;
}edge[(max_n*max_n)<<1];
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
void adde(int x,int y,int c){
	add_edge(x,y,c);
	add_edge(y,x,0);
}
bool bfs(int s,int t){
	memset(d,0,sizeof(d));
	queue<int> q;
	d[s]=1;
	q.push(s);
	while(!q.empty()){
		int p=q.front();
		q.pop();
		for(int i=head[p];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(!d[v]&&edge[i].cab>edge[i].flow){
				d[v]=d[p]+1;
				q.push(v);
				if(v==t) return true;
			}
		}
	}
	return false;
}
int dfs(int s,int flow,int t){
	if(s==t) return flow;
	int rest=flow;
	for(int i=head[s];i!=-1&&rest;i=edge[i].nxt){
		int v=edge[i].to;
		if(d[v]==d[s]+1&&edge[i].cab>edge[i].flow){
			int k=dfs(v,min(rest,edge[i].cab-edge[i].flow),t);
			if(!k) d[v]=0;
			edge[i].flow+=k;
			edge[i^1].flow-=k;
			rest-=k;
		}
	}
	return flow-rest;
}
int dinic(int s,int t){
	int maxflow=0;
	while(bfs(s,t)){
		maxflow+=dfs(s,inf,t);
	}
	return maxflow;
}
int main(){
	while(scanf("%d %d %d %d",&n,&np,&nc,&m)!=EOF){
		init();
		int x,y,c;
		for(int i=0;i<m;i++){
			scanf("%*1s%d%*1s%d%*1s%d",&x,&y,&c);
			adde(x+1,y+1,c);
		}
		for(int i=0;i<np;i++){
			scanf("%*1s%d%*1s%d",&x,&c);
			adde(0,x+1,c);
		}
		for(int i=0;i<nc;i++){
			scanf("%*1s%d%*1s%d",&x,&c);
			adde(x+1,n+1,c);
		}
		printf("%d\n",dinic(0,n+1));
	}
	return 0;
}
