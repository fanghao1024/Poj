#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
ll a,b;
int now;
int num[15];
ll dp[15][15];
ll dfs(int len,ll sum,bool lead,bool limit){
	if(len==0) return sum;
	if(!limit&&!lead&&dp[len][sum]!=-1) return dp[len][sum];
	int up=limit?num[len]:9;
	ll ans=0;
	for(int i=0;i<=up;i++){
		if(i==0&&lead) ans+=dfs(len-1,sum,lead,limit&&i==up);
		else if(i==now) ans+=dfs(len-1,sum+1,0,limit&&i==up);
		else if(i!=now) ans+=dfs(len-1,sum,0,limit&&i==up);
	}
	if(!limit&&!lead) dp[len][sum]=ans;
	return ans;
}
ll solve(ll x){
	int len=0;
	while(x){
		num[++len]=x%10;
		x/=10;
	}
	memset(dp,-1,sizeof(dp));
	return dfs(len,0,1,1);
}
int main(){
	while(scanf("%lld %lld",&a,&b)!=EOF){
		if(a==0&&b==0) break;
		if(a>b) swap(a,b);
		for(int i=0;i<=9;i++){
			if(i) printf(" ");
			now=i;
			printf("%lld",solve(b)-solve(a-1));
		}
		printf("\n");
	}
	return 0;
}
