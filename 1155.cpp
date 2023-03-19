#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=3010;
const int inf=0x3f3f3f3f;
int head[max_n],siz[max_n],sum[max_n];
int dp[max_n][max_n],val[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];

int N,M,cnt;
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	
	memset(siz,0,sizeof(siz));
	memset(sum,0,sizeof(sum));
	cnt=0;
}

void dfs(int u){
	if(head[u]==-1){
		siz[u]=1;
		sum[u]=val[u];
		dp[u][1]=val[u];
		dp[u][0]=0;
	}
	else siz[u]=0,sum[u]=0;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to,w=edge[i].w;
		dfs(v);
		siz[u]+=siz[v];
		sum[u]+=sum[v];
		for(int j=siz[u];j>=0;j--){
			for(int k=1;k<=siz[v];k++){
				dp[u][j]=max(dp[u][j],dp[v][k]+dp[u][j-k]-w);
			}
		}
	}
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		int k,a,c;
		init();
		for(int i=1;i<=N-M;i++){
			scanf("%d",&k);
			while(k--){
				scanf("%d %d",&a,&c);
				add_edge(i,a,c);
			}
		}
		for(int i=N-M+1;i<=N;i++) scanf("%d",&val[i]);
		for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) dp[i][j]=-inf;
		dfs(1);
		int ans;
		for(int i=siz[1];i>=0;i--) if(dp[1][i]>=0){ans=i;break;}
		printf("%d\n",ans);
	}
	return 0;
}
