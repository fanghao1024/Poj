#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_m=1010;
const int max_n=105;
const int inf=0x3f3f3f3f;
int M,N,cnt;
int pigs[max_m],head[max_n],belong[max_m],d[max_n];
struct Edge{
	int to,nxt;
	int cab,flow;
}edge[10100];
void add_edge(int x,int y,int c){
	edge[cnt].to=y;
	edge[cnt].cab=c;
	edge[cnt].flow=0;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
bool bfs(int s,int t){
	memset(d,0,sizeof(d));
	queue<int> q;
	q.push(s);
	d[s]=1;
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
	scanf("%d %d",&M,&N);
	for(int i=1;i<=M;i++) scanf("%d",pigs+i);
	memset(head,-1,sizeof(head));
	memset(belong,0,sizeof(belong));
	cnt=0;
	for(int i=1;i<=N;i++){
		int k,x;
		int w=0;
		scanf("%d",&k);
		while(k--){
			scanf("%d",&x);
			if(belong[x]==0){
				w+=pigs[x];
			}else{
				add_edge(belong[x],i,inf);
				add_edge(i,belong[x],0);
			}
			belong[x]=i;
		}
		add_edge(0,i,w);
		add_edge(i,0,0);
		scanf("%d",&x);
		add_edge(i,N+1,x);
		add_edge(N+1,i,0);
	}
	printf("%d\n",dinic(0,N+1));
	return 0;
}
