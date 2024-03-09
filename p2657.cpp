#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=12;
int num[max_n];
ll dp[max_n][max_n];
ll a,b;
ll dfs(int pos,int last,bool lead,bool limit){
	if(pos==0) return 1;
	if(!lead&&!limit&&dp[pos][last]!=-1) return dp[pos][last];
	int up=limit?num[pos]:9;
	ll ans=0;
	for(int i=0;i<=up;i++){
		if(abs(i-last)<2) continue;
		if(i==0&&lead) ans+=dfs(pos-1,-2,lead,limit&&i==up);
		else ans+=dfs(pos-1,i,0,limit&&i==up);
	}
	if(!limit&&!lead) dp[pos][last]=ans;
	return ans;
}
ll solve(ll x){
	int len=0;
	while(x){
		num[++len]=x%10;
		x/=10;
	}
	memset(dp,-1,sizeof(dp));
	return dfs(len,-2,1,1);
}
int main(){
	scanf("%lld %lld",&a,&b);
	printf("%lld\n",solve(b)-solve(a-1));
	return 0;
}

