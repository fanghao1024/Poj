#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int max_n=1024;
const int max_m=1e5+10;
const int inf=0x3f3f3f3f;
int T,N,M,F,cnt;
int head[max_n],dep[max_n],res[max_n];
struct Edge{
	int to,nxt;
	int cap,flow;
}edge[max_m<<1];
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void add_edge(int x,int y,int c){
	edge[cnt].to=y;
	edge[cnt].cap=c;
	edge[cnt].flow=0;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void adde(int x,int y,int c){
	add_edge(x,y,c);
	add_edge(y,x,0);
}
bool bfs(int s,int t){
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(!dep[v]&&edge[i].cap>edge[i].flow){
				dep[v]=dep[u]+1;
				q.push(v);
				if(v==t) return true;
			}
		}
	}
	return false;
}
int dfs(int u,int flow,int t){
	if(u==t) return flow;
	int rest=flow;
	for(int i=head[u];i!=-1&&rest;i=edge[i].nxt){
		int v=edge[i].to;
		if(dep[v]==dep[u]+1&&edge[i].cap>edge[i].flow){
			int k=dfs(v,min(rest,edge[i].cap-edge[i].flow),t);
			if(!k) dep[v]=0;
			edge[i].flow+=k;
			edge[i^1].flow-=k;
			rest-=k;
		}
	}
	return flow-rest;
}
int dinic(int s,int t){
	int maxflow=0;
	while(bfs(s,t)) maxflow+=dfs(s,inf,t);
	return maxflow;
}
int main(){
	scanf("%d",&T);
	for(int caseNo=1;caseNo<=T;caseNo++){
		scanf("%d%d%d",&N,&M,&F);
		init();
		int s=1,t=N+1;
		int x,y,w;
		for(int i=0;i<M;i++){
			scanf("%d %d %d",&x,&y,&w);
			adde(x,y,w);
		}
		int tot=0;
		for(int i=0;i<F;i++){
			scanf("%d %d",&x,&w);
			tot+=w;
			adde(x,t,w);
		}
		printf("Case %d: %d\n",caseNo,tot-dinic(s,t));
		tot=0;
		for(int i=0;i<2*M;i+=2){
			int u=edge[i^1].to,v=edge[i].to;
			if(dep[u]&&!dep[v]) res[tot++]=i/2;
		}
		printf("%d",tot);
		for(int i=0;i<tot;i++) printf(" %d",res[i]+1);
		printf("\n");
	}
	return 0;
}
