#include<cstdio>
#include<cstring>

int dp[20][2],num[20];
int N,M;
int dfs(int pos,bool states,bool limit){
	if(pos==0) return 1;
	if(!limit&&dp[pos][states]!=-1) return dp[pos][states];
	int len=limit?num[pos]:9;
	int ans=0;
	for(int i=0;i<=len;i++){
		if(states&&i==2) continue;
		if(i==4) continue;
		ans+=dfs(pos-1,i==6,limit&&i==len);
	}
	if(!limit) dp[pos][states]=ans;
	return ans;
}	
int solve(int m){
	int pos=0;
	while(m){
		num[++pos]=m%10;
		m/=10;
	}
	return dfs(pos,0,1);
}
int main(){
	memset(dp,-1,sizeof(dp));
	while(scanf("%d %d",&N,&M)&&(N+M)){
		printf("%d\n",solve(M)-solve(N-1));
	}
	return 0;
}
