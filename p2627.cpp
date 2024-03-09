#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;

ll num[max_n],sum[max_n],ds[max_n];
ll dp[max_n];
int q[max_n];
int N,K;
int main(){
	scanf("%d %d",&N,&K);
	sum[0]=0;
	for(int i=1;i<=N;i++) scanf("%lld",&num[i]),sum[i]=sum[i-1]+num[i];
	int f=0,r=0;
	for(int i=1;i<=N;i++){
		ds[i]=dp[i-1]-sum[i];
		while(f<r&&ds[q[r]]<ds[i]) r--;
		q[++r]=i;
		while(f<r&&q[f]<i-K) f++;
		dp[i]=ds[q[f]]+sum[i];
	}
	
	printf("%lld\n",dp[N]);
	return 0;
}
