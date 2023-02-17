#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
int rec[max_n][max_n];
int N,M;
int dp[max_n];
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		if(N==0&&M==0) break;
		for(int i=1;i<=N;i++){
			for(int j=1;j<=M;j++){
				scanf("%d",&rec[i][j]);
			}
		}
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=N;i++){
			for(int j=M;j>=0;j--){
				for(int k=1;k<=j;k++){
					dp[j]=max(dp[j],dp[j-k]+rec[i][k]);
				}
			}
		}
		//int ans=-1;
		//for(int i=1;i<=M;i++) ans=max(ans,dp[i]);
		//printf("%d\n",ans);
		printf("%d\n",dp[M]);
	}
	return 0;
}
