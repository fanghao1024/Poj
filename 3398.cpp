#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=10010;
const int inf=0x3f3f3f3f;
int N,cnt;
int head[max_n];
int dp[max_n][3];
struct Edge{
	int to,nxt;
}edge[max_n<<1];
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs(int u,int fa){
	dp[u][0]=1;
	dp[u][1]=0;
	dp[u][2]=max_n;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa){
			continue;
		}
		dfs(v,u);
		dp[u][0]+=min(dp[v][1],dp[v][0]);
		dp[u][1]+=dp[v][2];
	}
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa){
			dp[u][2]=min(dp[u][2],dp[u][1]-dp[v][2]+dp[v][0]);
		}
	}
}
int main(){
	while(scanf("%d",&N)!=EOF){
		cnt=0;
		int x,y;
		memset(head,-1,sizeof(head));
		for(int i=1;i<N;i++){
			scanf("%d %d",&x,&y);
			add_edge(x,y);
			add_edge(y,x);
		}
		dfs(1,0);
		printf("%d\n",min(dp[1][0],dp[1][2]));
		int mark;
		scanf("%d",&mark);
		if(mark==-1) break;
	}
	return 0;
}
