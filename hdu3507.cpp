#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=500010;
int s[max_n],dp[max_n],Q[max_n];
int st,ed,N,M;
int getY(int i,int j){
	return dp[i]+s[i]*s[i]-dp[j]-s[j]*s[j];
}
int getX(int i,int j){
	return s[i]-s[j];
}
int getV(int i,int j){
	return dp[j]+(s[i]-s[j])*(s[i]-s[j])+M;
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		for(int i=1;i<=N;i++) scanf("%d",&s[i]);
		s[0]=0;
		for(int i=1;i<=N;i++) s[i]+=s[i-1];
		st=ed=0;
		Q[ed++]=0;
		dp[0]=0;
		for(int i=1;i<=N;i++){
			while(st+1<ed&&getY(Q[st+1],Q[st])<=2*s[i]*getX(Q[st+1],Q[st])) st++;
			dp[i]=getV(i,Q[st]);
			while(st+1<ed&&getY(i,Q[ed-1])*getX(Q[ed-1],Q[ed-2])<=getY(Q[ed-1],Q[ed-2])*getX(i,Q[ed-1])) ed--;
			Q[ed++]=i;
		}
		printf("%d\n",dp[N]);
	}
	return 0;
}

