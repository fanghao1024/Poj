#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=6e3+10;

int N,cnt;
int R[max_n],indeg[max_n];
int head[max_n],dp[max_n][2];
struct Edge{
	int to;
	int nxt;
}edge[max_n<<1];

void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void dfs(int u){
	dp[u][0]=0;
	dp[u][1]=R[u];
	
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		dfs(v);
		dp[u][0]+=max(dp[v][0],dp[v][1]);
		dp[u][1]+=dp[v][0];
	}
	
}
int main(){
	scanf("%d",&N);
	init();
	for(int i=1;i<=N;i++) scanf("%d",&R[i]);
	int x,y;
	for(int i=1;i<N;i++) scanf("%d %d",&x,&y),add_edge(y,x),indeg[x]++;
	int root;
	for(int i=1;i<=N;i++) if(!indeg[i]){root=i;break;}
	dfs(root);
	printf("%d\n",max(dp[root][0],dp[root][1]));
	return 0;
}
