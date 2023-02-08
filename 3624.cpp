#include<cstdio>
#include<cstring>

int N,M;
const int max_n=3410;
const int max_m=12900;
int dp[max_m];
int W[max_n];
int D[max_n];
int main(){
	while(scanf("%d%d",&N,&M)!=EOF){
		for(int i=1;i<=N;i++){
			scanf("%d %d",&W[i],&D[i]);
		}
		memset(dp,-1,sizeof(dp));
		dp[0]=0;
		for(int i=1;i<=N;i++){
			for(int j=M;j>0;j--){
				if(j>=W[i]&&dp[j-W[i]]>=0){
					dp[j]=dp[j]>(dp[j-W[i]]+D[i])?dp[j]:(dp[j-W[i]]+D[i]);
				}
			}
		}
		int ans=0;
		for(int i=1;i<=M;i++){
			ans=ans>dp[i]?ans:dp[i];
		}
		printf("%d\n",ans);
	}	
	return 0;
}
