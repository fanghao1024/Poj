#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
ll a,b;
int num[15];
ll dp[15][12][12][2][2][2];
/*
ll dfs(int pos,int last,int samenum,bool limit,bool flag,bool eight,bool four){
	if(pos==0) return samenum>=2||flag;
	if(!limit&&dp[pos][last]!=-1) return dp[pos][last];
	int up=limit?num[pos]:9;
	ll ans=0;
	for(int i=0;i<=up;i++){
		if(i==4&&eight) continue;
		if(i==8&&four) continue;
		if(i!=last) ans+=dfs(pos-1,i,0,limit&&i==up,flag,eight||i==8,four||i==4);
		else ans+=dfs(pos-1,i,samenum+1,limit&&i==up,flag||samenum+1>=2,eight||i==8,four||i==4);
	}
	if(!limit) dp[pos][last]=ans;
	return ans;
}
 */
ll Dfs(int pos,int u,int v,bool state,bool n8,bool n4,bool limit){
	ll ans=0;
	if(n8&&n4) return 0;
	if(!pos) return state;
	if(!limit&&dp[pos][u][v][state][n8][n4]!=-1) return dp[pos][u][v][state][n8][n4];
	int up=limit?num[pos]:9;
	for(int i=0;i<=up;i++){
		ans+=Dfs(pos-1,i,u,(u==v&&u==i)||state,n8||i==8,n4||i==4,limit&&i==up);
	}
	if(!limit) dp[pos][u][v][state][n8][n4]=ans;
	return ans;
}
ll solve(ll x){
	int len=0;
	while(x){
		num[++len]=x%10;
		x/=10;
	}
	if(len!=11) return 0;
	memset(dp,-1,sizeof(dp));
	ll ans=0;
	for(int i=1;i<=num[len];i++) ans+=Dfs(len-1,i,0,0,i==8,i==4,i==num[len]);
	return ans;
	//return dfs(len,-1,0,1,0,0,0);
}
int main(){
	scanf("%lld %lld",&a,&b);
	printf("%lld\n",solve(b)-solve(a-1));
	return 0;
}
