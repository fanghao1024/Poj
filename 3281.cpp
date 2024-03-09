#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=105<<2;
const int inf=0x3f3f3f3f;
int N,F,D,cnt;
int head[max_n],dep[max_n],now[max_n],pre[max_n],g[max_n];
struct Edge{
	int to,nxt;
	int cap,flow;
}edge[(max_n*max_n)<<1];
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

void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void bfs(int t){
	memset(dep,0,sizeof(dep));
	memset(g,0,sizeof(g));
	dep[t]=1;
	queue<int> q;
	q.push(t);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		g[dep[u]]++;
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(!dep[v]&&!edge[i].cap){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
}
int augment(int s,int t){
	int u=t;
	int d=inf;
	while(u!=s){
		int e=pre[u];
		d=min(d,edge[e].cap-edge[e].flow);
		u=edge[e^1].to;
	}
	u=t;
	while(u!=s){
		int e=pre[u];
		edge[e].flow+=d;
		edge[e^1].flow-=d;
		u=edge[e^1].to;
	}
	return d;
}
int isap(int s,int t,int n){
	bfs(t);
	int u=s;
	int ans=0;
	memcpy(now,head,sizeof(head));
	while(dep[s]<=n){
		if(u==t){
			ans+=augment(s,t);
			u=s;
		}
		bool ok=0;
		for(int i=now[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]==dep[u]-1&&edge[i].cap>edge[i].flow){
				ok=1;
				pre[v]=i;
				now[u]=i;
				u=v;
				break;
			}
		}
		if(!ok){
			if(!--g[dep[u]]) break;
			int mindep=n+5;
			for(int i=head[u];i!=-1;i=edge[i].nxt){
				int v=edge[i].to;
				if(edge[i].cap>edge[i].flow&&mindep>dep[v]){
					mindep=dep[v];
				}
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
	int nf,nd,f,d;
	//while(scanf("%d%d%d",&N,&F,&D)!=EOF){
		scanf("%d%d%d",&N,&F,&D);
		init();
		int s=0,t=2*N+F+D+1;
		for(int i=1;i<=N;i++){
			adde(i+F,i+F+N,1);
			scanf("%d %d",&nf,&nd);
			while(nf--){
				scanf("%d",&f);
				adde(f,i+F,1);
			}
			while(nd--){
				scanf("%d",&d);
				adde(i+F+N,2*N+F+d,1);
			}
		}
		for(int i=1;i<=F;i++) adde(s,i,1);
		for(int i=1;i<=D;i++) adde(2*N+F+i,t,1);
		printf("%d\n",isap(s,t,t+1));
	//}
	return 0;
}
