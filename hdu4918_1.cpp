#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=101000;
int N,Q,cnt,tot,root,S,pl,ans;
int head[max_n],rec[max_n],f[max_n],s[max_n],cur[max_n],ids[max_n],Fa[max_n];
int Pool[max_n*40],dis[20][max_n];
bool vis[max_n];
struct Edge{
	int to,nxt;
}edge[max_n<<1];
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
struct Bit{
	int *C,n;
	void init(int T){
		n=T;
		C=Pool+pl;
		pl+=n+1;
		for(int i=0;i<=n;i++) C[i]=0;
	}
	void update(int x,int d){
		x++;
		for(int i=x;i<=n;i+=(i&-i)){
			C[i]+=d;
		}
	}
	int que(int x){
		x++;
		int res=0;
		for(int i=x;i>0;i-=(i&-i)){
			res+=C[i];
		}
		return res;
	}
}bit[max_n][2];

void init(){
	cnt=tot=root=pl=0;
	S=N;
	f[0]=max_n+10;
	cur[0]=0;
	ids[0]=0;
	memset(head,-1,sizeof(head));
	memset(vis,0,sizeof(vis));
}
void get_root(int u,int fa){
	s[u]=1;
	f[u]=0;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]&&v!=fa){
			get_root(v, u);
			s[u]+=s[v];
			f[u]=max(f[u],s[v]);
		}
	}
	f[u]=max(f[u],S-s[u]);
	if(f[u]<f[root]) root=u;
}
void dfs(int cur_dep,int idx,int u,int d,int fa){
	dis[cur_dep][u]=d;
	bit[idx][0].update(dis[cur_dep][u],rec[u]);
	if(cur_dep>1) bit[idx][1].update(dis[cur_dep-1][u],rec[u]);
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]&&v!=fa){
			dfs(cur_dep,idx,v,d+1,u);
		}
	}
}
void solve(int u,int fa){
	vis[u]=true;
	ids[u]=++tot;
	Fa[ids[u]]=ids[fa];
	cur[ids[u]]=cur[ids[fa]]+1;
	bit[ids[u]][0].init(S+1);
	bit[ids[u]][1].init(S+1);
	dfs(cur[ids[u]],ids[u],u,0,0);
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]&&v!=fa){
			root=0;
			S=s[v];
			get_root(v, 0);
			solve(root,u);
		}
	}
}
void update(int idx,int x,int d){
	bit[idx][0].update(dis[cur[idx]][x], d);
	if(Fa[idx]){
		bit[idx][1].update(dis[cur[idx]-1][x],d);
		update(Fa[idx],x,d);
	}
}
void query(int idx,int x,int k){
	int d=max(-1,min(bit[idx][0].n-1,k-dis[cur[idx]][x]));
	ans+=bit[idx][0].que(d);
	if(Fa[idx]){
		d=max(-1,min(bit[idx][1].n-1,k-dis[cur[idx]-1][x]));
		ans-=bit[idx][1].que(d);
		query(Fa[idx],x,k);
	}
}
int main() {
	while(scanf("%d %d",&N,&Q)!=EOF){
		for(int i=1;i<=N;i++) scanf("%d",&rec[i]);
		init();
		int x,y;
		for(int i=1;i<N;i++){
			scanf("%d%d",&x,&y);
			add_edge(x, y);
			add_edge(y, x);
		}

		get_root(1,0);
		solve(root,0);
		char ch[3];
		for(int i=1;i<=Q;i++){
			scanf("%s %d %d",ch,&x,&y);
			if(ch[0]=='!'){
				update(ids[x],x,y-rec[x]);
				rec[x]=y;
			}else{
				ans=0;
				query(ids[x],x,y);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}