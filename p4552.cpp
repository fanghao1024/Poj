#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;
int N;
ll dp[max_n];

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%lld",dp+i);
	}
	ll p=0,q=0;
	for(int i=N;i>=2;i--){
		dp[i]-=dp[i-1];
		if(dp[i]>0) p+=dp[i];
		else if(dp[i]<0) q-=dp[i];
	}
	printf("%lld\n",max(p,q));
	printf("%lld\n",max(p,q)-min(p,q)+1);
	return 0;
}
