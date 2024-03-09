#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=23;
int dp[2][1<<20];
int val[max_n][max_n];
int N;
int main(){
	while(scanf("%d",&N)!=EOF){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				scanf("%d",&val[i][j]);
			}
		}
		int now,old;
		now=0;
		old=1;
		memset(dp,0,sizeof(dp));
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				swap(now,old);
				memset(dp[now],0,sizeof(dp[now]));
				for(int S=0;S<(1<<N);S++){
					if(!(S&1)&&!(S&(1<<(N-1)))) dp[now][(S<<1&(~(1<<N)))^1]=max(dp[now][(S<<1&(~(1<<N)))^1],dp[old][S]+val[i][j]);
					dp[now][S<<1&(~(1<<N))]=max(dp[now][S<<1&(~(1<<N))],dp[old][S]);
				}
			}
		}
		int ans=0;
		for(int S=0;S<(1<<N);S++) ans=max(ans,dp[now][S]);
		printf("%d\n",ans);
	}
	return 0;
}
