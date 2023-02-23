#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e4+10;
int N,S;
int T[max_n],F[max_n],Q[max_n],dp[max_n];
int st,ed;
int getY(int i,int j){
	return dp[i]-dp[j];
}
int getX(int i,int j){
	return F[i]-F[j];
}
int getV(int i,int j){
	return dp[j]+(F[i]-F[j])*T[i]+S*(F[N]-F[j]);
}
int main(){
	while(scanf("%d",&N)!=EOF){
		scanf("%d",&S);
		for(int i=1;i<=N;i++) scanf("%d %d",&T[i],&F[i]);
		for(int i=2;i<=N;i++) T[i]+=T[i-1],F[i]+=F[i-1];
		T[0]=F[0]=0;
		st=ed=0;
		Q[ed++]=0;
		dp[0]=0;
		for(int i=1;i<=N;i++){
			while(st+1<ed&&getY(Q[st+1],Q[st])<=(S+T[i])*getX(Q[st+1],Q[st])) st++;
			dp[i]=getV(i,Q[st]);
			while(st+1<ed&&getY(i,Q[ed-1])*getX(Q[ed-1],Q[ed-2])<=getY(Q[ed-1],Q[ed-2])*getX(i,Q[ed-1])) ed--;
			Q[ed++]=i;
		}
		printf("%d\n",dp[N]);
	}
	return 0;
}
