#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=20010;
const int max_m=200010;
const int inf=0x3f3f3f3f;

int head[max_n],dep[max_n],g[max_n],pre[max_n],now[max_n];
struct Edge{
	int to,nxt;
	int cap,flow;
}edge[(max_m+2*max_n)<<1];
int N,M,cnt;
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
void bfs(int t){
	memset(dep,0,sizeof(dep));
	memset(g,0,sizeof(g));
	queue<int> q;
	q.push(t);
	dep[t]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		g[dep[u]]++;
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(!dep[v]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
}
int isap(int s,int t,int n){
	bfs(t);
	int u=s;
	int ans=0,d;
	memcpy(now,head,sizeof(head));
	while(dep[s]<=n){
		if(u==s) d=inf;
		int i=now[u];
		for(;i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]==dep[u]-1&&edge[i].cap>edge[i].flow){
				d=min(d,edge[i].cap-edge[i].flow);
				pre[v]=i;
				now[u]=i;
				u=v;
				if(u==t){
					while(u!=s){
						int e=pre[u];
						edge[e].flow+=d;
						edge[e^1].flow-=d;
						u=edge[e^1].to;
					}
					ans+=d;
				}
				break;
			}
		}
		if(i==-1){
			if(!--g[dep[u]]) break;
			int mindep=n+5;
			for(int j=head[u];j!=-1;j=edge[j].nxt){
				int v=edge[j].to;
				if(edge[j].cap>edge[j].flow&&dep[v]<mindep) mindep=dep[v];
			}
			dep[u]=mindep+1;
			now[u]=head[u];
			g[dep[u]]++;
			if(u!=s) u=edge[pre[u]^1].to;
		}
	}
	return ans;
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
		scanf("%d%d%d",&x,&y,&w);
		add_edge(x,y,w);
		add_edge(y,x,w);
	}
	printf("%d\n",isap(s,t,t+1));
	return 0;
}
