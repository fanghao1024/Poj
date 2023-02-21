#include<cstdio>
#include<cstring>

int a,b;
int dp[40][40][40];
int num[40];
int dfs(int pos,int num0,int num1,int lead,int limit){
	if(pos==-1) return num0>=num1;
	if(!limit&&dp[pos][num0][num1]!=-1) return dp[pos][num0][num1];
	int len=limit?num[pos]:1;
	int ans=0;
	for(int i=0;i<=len;i++){
		if(i==0&&lead) ans+=dfs(pos-1,num0,num1,lead,limit&(i==len));
		else ans+=dfs(pos-1,num0+(i==0),num1+(i==1),0,limit&(i==len));
	}
	if(!limit) dp[pos][num0][num1]=ans;
	return ans;
}
int solve(int m){
	int cnt=0;
	while(m){
		num[cnt++]=m%2;
		m/=2;
	}
	return dfs(cnt-1,0,0,1,1);
}
int main(){
	memset(dp,-1,sizeof(dp));
	while(scanf("%d %d",&a,&b)!=EOF){
		printf("%d\n",solve(b)-solve(a-1));
	}
	return 0;
}

