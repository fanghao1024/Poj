#include<cstdio>
#include<cstring>

int dp[20][2],num[20];
int N,M;
int dfs(int pos,bool sta,bool limit){
	if(pos==0) return 1;
	if(!limit&&dp[pos][sta]!=-1) return dp[pos][sta];
	int len=limit?num[pos]:9;
	int ans=0;
	for(int i=0;i<=len;i++){
		if(sta&&i==2) continue;
		if(i==4) continue;
		ans+=dfs(pos-1,i==6,limit&&i==len);
	}
	if(!limit) dp[pos][sta]=ans;
	return ans;
}
int solve(int m){
	int cnt=0;
	while(m){
		num[++cnt]=m%10;
		m/=10;
	}
	return dfs(cnt,0,1);
}
int main(){
	memset(dp,-1,sizeof(dp));
	while(scanf("%d %d",&N,&M)&&(N+M)){
		printf("%d\n",solve(M)-solve(N-1));
	}
	return 0;
}
