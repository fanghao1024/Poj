#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=15;
const int inf=0x3f3f3f3f;
int N;
int g[max_n][max_n];
int dp[(1<<11)][max_n];

void floyd(){
	for(int k=0;k<=N;k++){
		for(int i=0;i<=N;i++){
			for(int j=0;j<=N;j++){
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
			}
		}
	}
}
void traveling(int s,int u){
	for(int i=s-1;i>=0;i--){
		for(int u=0;u<=N;u++){
			for(int v=0;v<=N;v++){
				if(!u&&!(i>>u&1)) continue;
				if(!(i>>v&1)&&dp[i][u]>dp[i|1<<v][v]+g[u][v]){
					dp[i][u]=dp[i|1<<v][v]+g[u][v];
				}
			}
		}
	}
}
int TSP(int S,int u){
	if(dp[S][u]!=-1) return dp[S][u];
	if(S==(1<<(N+1))-1&&u==0) return dp[S][u]=0;
	int ans=inf;
	for(int v=0;v<=N;v++){
		if(!(S>>v&1)&&g[u][v]!=inf){
			ans=min(ans,TSP(S|1<<v,v)+g[u][v]);
		}
	}
	return dp[S][u]=ans;
}
int main(){
	while(scanf("%d",&N)&&N){
		memset(dp,-1,sizeof(dp));
		memset(g,0x3f,sizeof(g));
		
		for(int i=0;i<=N;i++){
			for(int j=0;j<=N;j++){
				scanf("%d",&g[i][j]);
			}
		}
		floyd();
		printf("%d\n",TSP(0,0));
		///S=(1<<(N+1))-1;
		
	//	dp[S][0]=0;
		//traveling(S,0);
		//printf("%d\n",dp[0][0]);
	}
	
	return 0;
}
