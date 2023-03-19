#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
const int inf=0x3f3f3f3f;
int D[max_n],sum[max_n],N,dp[max_n][max_n];
int T;
int main(){
	scanf("%d",&T);
	int kase=1;
	while(T--){
		scanf("%d",&N);
		for(int i=1;i<=N;i++) scanf("%d",&D[i]),sum[i]=D[i]+sum[i-1];
		for(int i=1;i<=N;i++) dp[i][i]=0;
		for(int len=2;len<=N;len++){
			for(int i=1;i+len-1<=N;i++){
				int j=i+len-1;
				dp[i][j]=inf;
				for(int k=1;k<=j-i+1;k++){
					dp[i][j]=min(dp[i][j],dp[i+1][i+k-1]+(k-1)*D[i]+dp[i+k][j]+(sum[j]-sum[i+k-1])*k);
				}
			}
		}
		printf("Case #%d: %d\n",kase++,dp[1][N]);
	}
	return 0;
}
