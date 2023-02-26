#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=20010;
const int max_m=240010;
const int inf=0x3f3f3f3f;

int N,M,cnt;

int head[max_n],dep[max_n];
struct Edge{
	int to,nxt;
	int cap,flow;
}edge[max_m<<1];
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void add(int x,int y,int c){
	edge[cnt].to=y;
	edge[cnt].cap=c;
	edge[cnt].flow=0;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}

void adde(int x,int y,int c){
	add(x,y,c);
	add(y,x,0);
}
bool bfs(int s,int t){
	memset(dep,0,sizeof(dep));
	queue<int> q;
	q.push(s);
	dep[s]=1;
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
	scanf("%d %d",&N,&M);
		int s=0,t=N+1;
		init();
		int x,y,w;
		for(int i=1;i<=N;i++){
			scanf("%d %d",&x,&y);
			adde(s,i,x);
			adde(i,t,y);
		}
		for(int i=1;i<=M;i++){
			scanf("%d %d %d",&x,&y,&w);
			adde(x,y,w);
			adde(y,x,w);
		}
		printf("%d\n",dinic(s,t));
	
	return 0;
}
 
