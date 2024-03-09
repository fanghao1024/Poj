#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;

int head[max_n],cnt,N,Q,sum[max_n];
int dp[max_n][max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void dfs(int u,int father){
	
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to,w=edge[i].w;
		if(v==father) continue;
		dfs(v,u);
		sum[u]+=sum[v]+1;
		for(int j=min(sum[u],Q);j>=0;j--){
			for(int k=0;k<=min(sum[v],j-1);k++){
				dp[u][j]=max(dp[u][j],dp[v][k]+dp[u][j-k-1]+w);
			}
		}
	}
}
int main(){
	scanf("%d %d",&N,&Q);
	int x,y,w;
	init();
	for(int i=1;i<N;i++){
		scanf("%d %d %d",&x,&y,&w);
		add_edge(x,y,w);
		add_edge(y,x,w);
	}
	dfs(1,0);
	printf("%d\n",dp[1][Q]);
	return 0;
}
