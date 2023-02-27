#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e5+10;
const int inf=0x3f3f3f3f;

int dp[max_n],q[max_n];
int N,M;
int main(){
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++) scanf("%d",&dp[i]);
	for(int i=2;i<=N;i++) dp[i]+=dp[i-1];
	dp[0]=0;
	int f=0,r=-1;
	q[++r]=0;
	int ans=-inf;
	for(int i=1;i<=N;i++){
		while(f<=r&&q[f]<i-M) f++;
		ans=max(ans,dp[i]-dp[q[f]]);
		while(f<=r&&dp[q[r]]>dp[i]) r--;
		q[++r]=i;
		
	}
	printf("%d\n",ans);
	return 0;
}
