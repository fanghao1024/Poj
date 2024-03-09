#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e6+10;
int N,C;
ll num[max_n];
ll dp[max_n];
int Q[max_n];
ll getY(int i,int j){
	return dp[i]+num[i+1]*num[i+1]-dp[j]-num[j+1]*num[j+1];
}
ll getX(int i,int j){
	return num[i+1]-num[j+1];
}
ll getV(int i,int j){
	return dp[j]+(num[i]-num[j+1])*(num[i]-num[j+1])+C;
}
int main(){
	while(scanf("%d %d",&N,&C)!=EOF){
		if(!N&&!C) break;
		for(int i=1;i<=N;i++) scanf("%lld",num+i);
		dp[0]=0;
		int st=0,ed=0;
		Q[ed++]=0;
		for(int i=1;i<=N;i++){
			while(st+1<ed&&getY(Q[st+1],Q[st])<=2*num[i]*getX(Q[st+1],Q[st])) st++;
			dp[i]=getV(i,Q[st]);
			while(st+1<ed&&getY(i,Q[ed-1])*getX(Q[ed-1],Q[ed-2])<=getY(Q[ed-1],Q[ed-2])*getX(i,Q[ed-1])) ed--;
			Q[ed++]=i;
		}
		printf("%lld\n",dp[N]);
	}
	return 0;
}
