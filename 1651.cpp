#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=105;
int num[max_n];
int N;
int dp[max_n][max_n];
int solve(int n){
	for(int len=1;len<N-1;len++){
		for(int i=0;i+len<N-1;i++){
			//dp[i][i+len]=dp[i+1][i+len]+num[i-1]*num[i]*num[i+len];
			for(int k=i;k<i+len;k++)
				dp[i][i+len]=min(dp[i][i+len],dp[i][k]+dp[k+1][i+len]+num[i]*num[k]*num[i+1+len]);
		}
	}
	return dp[0][n-1];
}
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;i++) scanf("%d",&num[i]);
	memset(dp,0,sizeof(dp));
	//for(int i=0;i<N-1;i++) dp[i][i]=0;
	for(int len=1;len<N-1;len++){
		for(int i=0;i+len<N-1;i++){
			dp[i][i+len]=dp[i][i]+dp[i+1][i+len]+num[i]*num[i+1]*num[i+len+1];
			for(int k=i+1;k<i+len;k++)
				dp[i][i+len]=min(dp[i][i+len],dp[i][k]+dp[k+1][i+len]+num[i]*num[k]*num[i+len+1]);
		}
	}
	printf("%d\n",dp[0][N-2]);
	printf("%d\n",solve(N-1));
	return 0;
}


