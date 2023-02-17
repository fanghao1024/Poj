#include<cstdio>
#include<cstring>
const int max_n=1024;
int rec[max_n];
int dp[max_n];
int N;
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",&rec[i]);
	dp[0]=0;
	for(int i=1;i<=N;i++){
		dp[i]=1;
		for(int j=1;j<i;j++){
			if(rec[i]>rec[j]){
				dp[i]=dp[i]>dp[j]+1?dp[i]:dp[j]+1;
			}
		}
	}
	int ans=-1;
	for(int i=1;i<=N;i++) ans=ans>dp[i]?ans:dp[i];
	printf("%d\n",ans);
	
	return 0;
}
