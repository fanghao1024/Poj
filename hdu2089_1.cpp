#include<cstdio>
#include<cstring>

int N,M;
int dp[15][2];
int dig[15];
int dfs(int pos,bool sta,int limit){
	if(pos==0)  return 1;
	if(!limit&&dp[pos][sta]!=-1) return dp[pos][sta];
	int len=limit?dig[pos]:9;
	int ans=0;
	for(int i=0;i<=len;i++){
		if(sta&&i==2) continue;
		if(i==4) continue;
		ans+=dfs(pos-1,i==6,limit&i==len);
	}
	if(!limit) dp[pos][sta]=ans;
	return ans;
}
int solve(int m){
	int pos=0;
	while(m){
		dig[++pos]=m%10;
		m/=10;
	}
	return dfs(pos,0,1);
}
int main(){
	memset(dp,-1,sizeof(dp));
	while(scanf("%d %d",&N,&M)!=EOF){
		if(!N&&!M) break;
		printf("%d\n",solve(M)-solve(N-1));
	}
	return 0;
}
