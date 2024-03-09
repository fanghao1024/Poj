#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=10;
const int max_m=32;
const int inf=0x3f3f3f3f;
int N,M,P,A,B;
int t[max_n];
double dp[1<<10][32],ans;
int g[max_m][max_m];
void solve(){
	ans=inf;
	for(int i=0;i<(1<<N);i++) fill(dp[i],dp[i]+M+1,inf);
	dp[(1<<N)-1][A]=0;
	for(int S=(1<<N)-1;S>=0;S--){
		for(int u=1;u<=M;u++){
			for(int i=0;i<N;i++){
				if(!(S>>i&1)) continue;
				for(int v=1;v<=M;v++){
					if(g[u][v]>0) dp[S&~(1<<i)][v]=min(dp[S][u]+g[u][v]/(t[i]+0.0),dp[S&~(1<<i)][v]);
				}
			}
		}
		ans=min(ans,dp[S][B]);
	}
}
int main(){
	while(scanf("%d%d%d%d%d",&N,&M,&P,&A,&B)&&(N+M+P+A+B)){
		for(int i=0;i<N;i++) scanf("%d",&t[i]);
		memset(g,-1,sizeof(g));
		int x,y,z;
		while(P--){
			scanf("%d %d %d",&x,&y,&z);
			g[x][y]=g[y][x]=z;
		}
		solve();
		if(ans<inf) printf("%.3f\n",ans);
		else printf("Impossible\n");
	}
	return 0;
}
