#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e5+10;

int head[max_n],dep[max_n];
int par[max_n][20];
int N,M,S,cnt;
struct Edge{
	int to,nxt;
}edge[max_n<<1];

void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
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
	for(int i=19;i>=0;i--){
		//if(dep[par[x][i]]>=dep[y]){
		if(dep[x]-(1<<i)>=dep[y]){
			x=par[x][i];
		}
	}
	if(x==y) return x;
	for(int i=19;i>=0;i--){
		if(par[x][i]!=par[y][i]){
			x=par[x][i];
			y=par[y][i];
		}
	}
	return par[x][0];
}
int main(){
	scanf("%d %d %d",&N,&M,&S);
	init();
	int x,y;
	for(int i=1;i<N;i++){
		scanf("%d %d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}
	dfs(S,0);
	while(M--){
		scanf("%d %d",&x,&y);
		printf("%d\n",LCA(x,y));
	}
	return 0;
}
