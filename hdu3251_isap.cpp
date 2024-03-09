#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=1024;
const int max_m=1e5+10;
const int inf=0x3f3f3f3f;

int head[max_n],dep[max_n],now[max_n],g[max_n],pre[max_n],res[max_n];
bool vis[max_n];
int T,N,M,F,cnt;
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
		int i=head[u];
		for(;i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]+1==dep[u]&&edge[i].cap>edge[i].flow){
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
			if(--g[dep[u]]==0) break;
			int mindep=n+5;
			for(int j=head[u];j!=-1;j=edge[j].nxt){
				int v=edge[j].to;
				if(edge[j].cap>edge[j].flow&&mindep>dep[v]) mindep=dep[v];
			}
			dep[u]=mindep+1;
			g[dep[u]]++;
			now[u]=head[u];
			if(u!=s) u=edge[pre[u]^1].to;
		}
	}
	return ans;
}
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]&&edge[i].cap>edge[i].flow){
			dfs(v);
		}
	}
}
int main(){
	scanf("%d",&T);
	for(int caseNo=1;caseNo<=T;caseNo++){
		scanf("%d %d %d",&N,&M,&F);
		int x,y,w;
		init();
		int s=1,t=N+1;
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
		printf("Case %d: %d\n",caseNo,tot-isap(s,t,t));
		memset(vis,0,sizeof(vis));
		dfs(s);
		tot=0;
		for(int i=0;i<2*M;i+=2){
			int u=edge[i^1].to,v=edge[i].to;
			if(vis[u]&&!vis[v]) res[tot++]=i/2;
		}
		printf("%d",tot);
		for(int i=0;i<tot;i++) printf(" %d",res[i]+1);
		printf("\n");
	}
	return 0;
}

