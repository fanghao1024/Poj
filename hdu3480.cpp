#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e4+10;
const int inf=0x3f3f3f3f;
int T,N,M,ind,st,ed;
int num[max_n];
int dp[max_n][2];
int Q[max_n];
int getY(int k1,int k2){
	return (num[k1+1]*num[k1+1]+dp[k1][ind^1])-(num[k2+1]*num[k2+1]+dp[k2][ind^1]);
}
int getX(int k1,int k2){
	return num[k1+1]-num[k2+1];
}
int getV(int i,int k){
	return dp[k][ind^1]+num[i]*num[i]-2*num[i]*num[k+1]+num[k+1]*num[k+1];
}
void solve(){
	ind=0;
	st=ed=0;
	Q[ed++]=0;
	dp[0][ind]=0;
	for(int i=1;i<=N;i++) dp[i][ind]=inf;
	for(int j=1;j<=M;j++){
		st=ed=0;
		ind^=1;
		Q[ed++]=0;
		for(int i=1;i<=N;i++){
			while(st+1<ed&&getY(Q[st+1],Q[st])<=2*num[i]*getX(Q[st+1],Q[st])) st++;
			dp[i][ind]=getV(i,Q[st]);
			while(st+1<ed&&getY(i,Q[ed-1])*getX(Q[ed-1],Q[ed-2])<=getY(Q[ed-1],Q[ed-2])*getX(i,Q[ed-1])) ed--;
			Q[ed++]=i;
		}
	}
}
int main(){
	scanf("%d",&T);
	for(int caseNo=1;caseNo<=T;caseNo++){
		scanf("%d %d",&N,&M);
		for(int i=1;i<=N;i++) scanf("%d",&num[i]);
		sort(num+1,num+N+1);
		solve();
		printf("Case %d: %d\n",caseNo,dp[N][ind]);
	}
	return 0;
}
