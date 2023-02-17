#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=6010;
int N,cnt;
int rec[max_n],dp[max_n][2];
int head[max_n];
bool boss[max_n];
struct Edge{
	int to,nxt;
}edge[max_n];
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs(int u){
	dp[u][0]=0;
	dp[u][1]=rec[u];
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		dfs(v);
		dp[u][0]+=max(dp[v][0],dp[v][1]);
		dp[u][1]+=dp[v][0];
	}
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",&rec[i]);
	rec[0]=0;
	memset(head,-1,sizeof(head));
	memset(boss,0,sizeof(boss));
	int x,y;
	cnt=0;
	while(scanf("%d %d",&x,&y)){
		if(x==0&&y==0) break;
		add_edge(y,x);
		boss[x]=1;
	}
	int root;
	for(int i=1;i<=N;i++){
		if(!boss[i]){
			root=i;
			break;
		}
	}
	add_edge(0,root);
	dfs(0);
	printf("%d\n",dp[0][0]);
	return 0;
}
