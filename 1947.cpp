#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=155;
const int inf=0x3f3f3f3f;

bool indeg[max_n];
int N,P,cnt,siz[max_n];
int head[max_n],dp[max_n][max_n],sonnum[max_n];
struct Edge{
	int to,nxt;
}edge[max_n<<1];

void init(){
	memset(head,-1,sizeof(head));
	memset(indeg,0,sizeof(indeg));
	memset(dp,0x3f,sizeof(dp));
	memset(siz,0,sizeof(siz));
	memset(sonnum,0,sizeof(sonnum));
	cnt=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs(int u){

	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		dfs(v);
		for(int j=P;j>1;j--){
			for(int k=1;k<j;k++){
				
				dp[u][j]=min(dp[u][j],dp[v][k]+dp[u][j-k]-1);
				
			}
		}
	}
}
int main(){
	scanf("%d %d",&N,&P);
	init();
	int x,y;
	for(int i=1;i<N;i++){
		scanf("%d %d",&x,&y);
		add_edge(x,y);
		indeg[y]=1;
		sonnum[x]++;
	}
	for(int i=1;i<=N;i++) dp[i][1]=sonnum[i];
	for(int i=1;i<=N;i++){
		if(!indeg[i]){
			dfs(i);
			int ans=dp[i][P];
			for(int j=1;j<=N;j++) ans=min(ans,dp[j][P]+1);
			printf("%d\n",ans);
			break;
		}
	}
	return 0;
}
