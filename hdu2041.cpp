#include<cstdio>

const int max_n=43;
int dp[max_n];
int N,v;
void init(){
	dp[1]=0;
	dp[2]=1;
	dp[3]=2;
	for(int i=4;i<=40;i++) dp[i]=dp[i-1]+dp[i-2];
}
int main(){
	init();
	scanf("%d",&N);
	while(N--){
		scanf("%d",&v);
		printf("%d\n",dp[v]);
	}
	return 0;
}
