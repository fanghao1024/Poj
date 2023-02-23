#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=15;
const int inf=0x3f3f3f3f;
int g[max_n][max_n];
int dp[1<<11][max_n];
int N;
void floyd(){
	for(int k=0;k<=N;k++){
		for(int i=0;i<=N;i++){
			for(int j=0;j<=N;j++){
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
			}
		}
	}
}
void TSP(int s,int p){
	dp[s][p]=0;
	for(int S=s-1;S>=0;S--){
		for(int u=0;u<=N;u++){
			for(int v=0;v<=N;v++){
				if(!u&&!(S>>u&1)||g[u][v]==inf) continue;
				if(!(S>>v&1)&&dp[S][u]>g[u][v]+dp[S|1<<v][v]){
					dp[S][u]=g[u][v]+dp[S|1<<v][v];
				}
			}
		}
	}
}
int main(){
	while(scanf("%d",&N)&&N){
		memset(dp,0x3f,sizeof(dp));
		memset(g,0x3f,sizeof(g));
		for(int i=0;i<=N;i++){
			for(int j=0;j<=N;j++){
				scanf("%d",&g[i][j]);
			}
		}
		floyd();
		TSP((1<<(N+1))-1,0);
		printf("%d\n",dp[0][0]);
	}
	return 0;
}
