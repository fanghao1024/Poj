#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e6+10;
int head[max_n],cnt,fa[max_n],mark;
ll dp[max_n][2];
bool vis[max_n];
struct Edge{
	int to,nxt;
}edge[max_n];

void init(){
	memset(head,-1,sizeof(head));
	memset(vis,0,sizeof(vis));
	cnt=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
int N,val[max_n];
ll ans;
int check_c(int u){
	vis[u]=1;
	int f=fa[u];
	if(vis[f]) return f;
	else return check_c(f);
}
void dfs(int u){
	dp[u][0]=0;
	dp[u][1]=val[u];
	vis[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==mark) continue;
		dfs(v);
		dp[u][0]+=max(dp[v][0],dp[v][1]);
		dp[u][1]+=dp[v][0];
	}
}
ll psedotree(int u){
	ll res=0;
	mark=check_c(u);
	dfs(mark);
	res=max(res,dp[mark][0]);
	mark=fa[mark];
	dfs(mark);
	res=max(res,dp[mark][0]);
	return res;
}
int main(){
	scanf("%d",&N);
	init();
	int x;
	for(int i=1;i<=N;i++){
		scanf("%d %d",&val[i],&x);
		add_edge(x,i);
		fa[i]=x;
	}
	ans=0;
	for(int i=1;i<=N;i++){
		if(!vis[i]) ans+=psedotree(i);
	}
	printf("%lld\n",ans);
	return 0;
}
