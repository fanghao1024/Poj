#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;
ll dp[max_n],A[max_n],B[max_n],C[max_n];
ll P[max_n];
int N,M;

int main(){
	scanf("%d %d",&N,&M);
	for(int i=1;i<=M;i++) scanf("%lld",&P[i]);
	for(int i=1;i<N;i++) scanf("%lld %lld %lld",&A[i],&B[i],&C[i]);
	for(int i=2;i<=M;i++){
		int x=P[i-1],y=P[i];
		if(x>y) swap(x,y);
		dp[x]++;
		if(y<N) dp[y]--;
	}
	ll ans=0;
	for(int i=1;i<N;i++){
		dp[i]+=dp[i-1];
		if(dp[i]*A[i]<C[i]+B[i]*dp[i]) ans+=dp[i]*A[i];
		else ans+=C[i]+B[i]*dp[i];
	}
	printf("%lld\n",ans);
	return 0;
}
