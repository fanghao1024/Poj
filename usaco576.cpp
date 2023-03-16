
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e4+10;

int N,K,cnt;
int head[max_n],dep[max_n],par[max_n][60],D[max_n],Sum[max_n];
struct Edge{
	int to,nxt;
}edge[max_n<<1];
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	memset(D,0,sizeof(D));
	memset(Sum,0,sizeof(Sum));
	cnt=0;
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	par[u][0]=fa;
	for(int i=1;(1<<i)<=dep[u];i++){
		par[u][i]=par[par[u][i-1]][i-1];
	}
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=16;i>=0;i--){
		if(dep[par[x][i]]>=dep[y]){
			x=par[x][i];
		}
	}
	if(x==y) return x;
	for(int i=16;i>=0;i--){
		if(par[x][i]!=par[y][i]){
			x=par[x][i];
			y=par[y][i];
		}
	}
	return par[x][0];
}
void dfs1(int u,int fa){
	Sum[u]=D[u];
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa){
			dfs1(v,u);
			Sum[u]+=Sum[v];
		}
	}
}
int main(){
	FILE *fin  = fopen ("maxflow.in", "r");
	FILE *fout = fopen ("maxflow.out", "w");
	fscanf(fin,"%d %d",&N,&K);
	int x,y;
	init();
	for(int i=1;i<N;i++){
		fscanf(fin,"%d %d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs(1,0);
	while(K--){
		fscanf(fin,"%d %d",&x,&y);
		int lca=LCA(x,y);
		D[x]++;D[y]++;D[lca]--;D[par[lca][0]]--;
	}
	dfs1(1,0);
	int ans=Sum[1];
	for(int i=2;i<=N;i++) ans=max(ans,Sum[i]);
	fprintf(fout,"%d\n",ans);
	return 0;
}
