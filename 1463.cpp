#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1510;
int N,cnt;
int head[max_n];
int dp[max_n][2];
bool vis[max_n];
struct Edge{
	int to,nxt;
}edge[max_n<<1];
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs(int u){
	vis[u]=1;
	dp[u][0]=0;
	dp[u][1]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(vis[v]) continue;
		dfs(v);
		dp[u][1]+=min(dp[v][0],dp[v][1]);
		dp[u][0]+=dp[v][1];
	}
}
int main(){
	int x,y,z;
	while(scanf("%d",&N)!=EOF){
		cnt=0;
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		for(int i=0;i<N;i++){
			scanf("%d:(%d)",&x,&y);
			for(int j=0;j<y;j++){
				scanf("%d",&z);
				add_edge(x,z);
				add_edge(z,x);
			}
		}
		dfs(0);
		printf("%d\n",min(dp[0][0],dp[0][1]));
	}
	return 0;
}
