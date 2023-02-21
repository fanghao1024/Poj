#include<cstdio>
#include<cstring>

typedef long long ll;
ll dp[40][2];
int dig[40];
int T;
ll N;
ll dfs(int pos,bool sta,int limit){
	if(!pos) return 1;
	if(!limit&&dp[pos][sta]!=-1) return dp[pos][sta];
	int len=limit?dig[pos]:9;
	ll ans=0;
	for(int i=0;i<=len;i++){
		if(i==9&&sta) continue;
		ans+=dfs(pos-1,i==4,limit&i==len);
	}
	if(!limit) dp[pos][sta]=ans;
	return ans;
}
ll solve(ll m){
	int pos=0;
	while(m){
		dig[++pos]=m%10;
		m/=10;
	}
	return dfs(pos,0,1)-1;
}
int main(){
	scanf("%d",&T);
	memset(dp,-1,sizeof(dp));
	while(T--){
		scanf("%lld",&N);
		printf("%lld\n",N-solve(N));
	}
	return 0;
}



