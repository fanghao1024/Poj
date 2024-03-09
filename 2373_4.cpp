#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxL=1e6+10;
const int inf=0x3f3f3f3f;
int N,L;
int A,B;
int S,E;
bool flag[maxL];
int dp[maxL];
int st,ed,Q[maxL];

void solve(){
	memset(dp,inf,sizeof(dp));
	dp[0]=0;
	st=ed=0;
	for(int i=2*A;i<=L;i+=2){
		while(st<ed&&dp[i-2*A]<=dp[Q[ed-1]]) ed--;
		Q[ed++]=i-2*A;
		while(st<ed&&Q[st]<i-2*B) st++;
		if(flag[i]) dp[i]=min(dp[i],dp[Q[st]]+1);
	}
	
	printf("%d\n",dp[L]<inf?dp[L]:-1);
}
int main(){
	while(scanf("%d %d",&N,&L)!=EOF){
		scanf("%d %d",&A,&B);
		memset(flag,1,sizeof(flag));
		while(N--){
			scanf("%d %d",&S,&E);
			for(int i=S+1;i<E;i++) flag[i]=0;
		}
		solve();
	}
	return 0;
}
