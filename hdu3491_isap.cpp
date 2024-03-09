#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=205;
const int max_m=1e4+10;
const int inf=0x3f3f3f3f;

int head[max_n],dep[max_n],g[max_n],now[max_n],pre[max_n];
int T,N,M,S,H,cnt;
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
void bfs(int t){
	memset(dep,0,sizeof(dep));
	memset(g,0,sizeof(g));
	queue<int> q;
	dep[t]=1;
	q.push(t);
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
	int ans=0;
	int d;
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
				if(edge[j].cap>edge[j].flow&&mindep<dep[v]) mindep=dep[v];
				dep[u]=mindep+1;
				g[dep[u]]++;
				now[u]=head[u];
				if(u!=s) u=edge[pre[u]^1].to;
			}
		}
	}
	return ans;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d %d",&N,&M,&S,&H);
		init();
		S+=N;
		int x,y;
		for(int i=1;i<=N;i++){
			scanf("%d",&x);
			adde(i,i+N,x);
		}
		for(int i=1;i<=M;i++){
			scanf("%d %d",&x,&y);
			adde(x+N,y,inf);
			adde(y+N,x,inf);
		}
		printf("%d\n",isap(S,H,2*N));
	}
	return 0;
}
