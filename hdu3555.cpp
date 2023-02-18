#include<cstdio>
#include<cstring>
#include<cmath>
typedef long long ll;
int T;
ll N;
ll dp[64][15];
int num[64];

void init(){
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(int i=1;i<=30;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=9;k++){
				if(j==4&&k==9) continue;
				dp[i][j]+=dp[i-1][k];
			}
		}
	}
}
ll solve(ll m){
	int cnt=0;
	while(m){
		num[++cnt]=m%10;
		m/=10;
	}
	num[cnt+1]=0;
	ll ans=0;
	for(int i=cnt;i>=1;i--){
		for(int j=0;j<num[i];j++)
		{
			if(j==9&&num[i+1]==4) continue;
			ans+=dp[i][j];
		}
		if(num[i]==9&&num[i+1]==4){
			ans--;
			break;
		}
	}
	return ans;
}
int main(){
	init();
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&N);
		printf("%lld\n",N-solve(N));
	}
	return 0;
}
