#include<cstdio>

const int max_n=2e5+10;
const int inf=0x3f3f3f3f;
int num[max_n];
int dp[max_n];
int n;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]);
	int ans=num[1];
	dp[1]=num[1];
	for(int i=2;i<=n;i++){
		dp[i]=dp[i-1]>0?dp[i-1]+num[i]:num[i];
		if(ans<dp[i]) ans=dp[i];
	}
	printf("%d\n",ans);
	return 0;
}
