#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[35][35][35];
int dig[35];
int a,b;
int dfs(int pos,int num0,int num1,int lead,int limit){
	if(pos==0) return num0>=num1;
	if(!limit&&!lead&&dp[pos][num0][num1]!=-1) return dp[pos][num0][num1];
	int len=limit?dig[pos]:1;
	int ans=0;
	for(int i=0;i<=len;i++){
		if(lead&&i==0) ans+=dfs(pos-1,num0,num1,lead,limit&&i==len);
		else ans+=dfs(pos-1,num0+(i==0),num1+(i==1),0,limit&&i==len);
	}
	if(!limit&&!lead) dp[pos][num0][num1]=ans;
	return ans;
}
int solve(int m){
	int pos=0;
	while(m){
		dig[++pos]=m%2;
		m/=2;
	}
	return dfs(pos,0,0,1,1);
}
int main(){
	memset(dp,-1,sizeof(dp));
	while(scanf("%d %d",&a,&b)!=EOF){
		printf("%d\n",solve(b)-solve(a-1));
	}
	return 0;
}
