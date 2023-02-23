#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=13;
const int max_m=32;
const int inf=0x3f3f3f3f;
int N,M,P,A,B;
int ticket[max_n];
int g[max_m][max_m];
double dp[1<<10][max_m],ans;
void solve(){
	for(int i=0;i<(1<<N);i++){
		fill(dp[i],dp[i]+M+1,inf);
	}
	dp[(1<<N)-1][A]=0;
	ans=inf;
	for(int S=(1<<N)-1;S>=0;S--){
		for(int u=1;u<=M;u++){
			for(int i=0;i<N;i++){
				if(!(S>>i&1))continue;
				for(int v=1;v<=M;v++){
					if(g[u][v]>0) dp[S&~(1<<i)][v]=min(dp[S&~(1<<i)][v],dp[S][u]+g[u][v]/(ticket[i]+0.0));
				}
			}
			
		}
		ans=min(ans,dp[S][B]);
	}
}
int main(){
	int x,y,z;
	while(scanf("%d%d%d%d%d",&N,&M,&P,&A,&B)&&(N+M+P+A+B)){
		for(int i=0;i<N;i++) scanf("%d",&ticket[i]);
		memset(g,-1,sizeof(g));
		while(P--){
			scanf("%d %d %d",&x,&y,&z);
			g[x][y]=g[y][x]=z;
		}
		solve();
		if(abs(ans-inf)<1e-3){
			printf("Impossible\n");
		}else{
			printf("%.3f\n",ans);
		}
	}
	return 0;
}

