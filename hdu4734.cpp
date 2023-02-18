#include<cstdio>
#include<cstring>

int T,A,B;
int dp[15][4700];
int dig[15];
int fa(int a){
	int res=0;
	int k=1;
	while(a){
		res+=(a%10)*k;
		k<<=1;
		a/=10;
	}
	return res;
}
int dfs(int pos,int f,int limit){
	if(pos==-1) return f>=0;
	if(f<0) return 0;
	if(!limit&&dp[pos][f]!=-1) return dp[pos][f];
	int len=limit?dig[pos]:9;
	int ans=0;
	for(int i=0;i<=len;i++){
		ans+=dfs(pos-1,f-i*(1<<pos),limit&i==len);
	}
	if(!limit) dp[pos][f]=ans;
	return ans;
}
int solve(int a,int b){
	int pos=0;
	while(b){
		dig[pos++]=b%10;
		b/=10;
	}
	return dfs(pos-1,fa(a),1);
}
int main(){
	scanf("%d",&T);
	memset(dp,-1,sizeof(dp));
	for(int caseNo=1;caseNo<=T;caseNo++){
		scanf("%d %d",&A,&B);
		printf("Case #%d: %d\n",caseNo,solve(A,B));
	}
	
	return 0;
}
