#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=1024;
int dp[max_n];
int val[max_n],wei[max_n];
int T,N,V;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&N,&V);
		for(int i=1;i<=N;i++) scanf("%d",&val[i]);
		for(int i=1;i<=N;i++) scanf("%d",&wei[i]);
		for(int i=0;i<=V;i++) dp[i]=0;
		for(int i=1;i<=N;i++){
			for(int j=V;j>=wei[i];j--){
				dp[j]=max(dp[j],dp[j-wei[i]]+val[i]);
			}
		}
		printf("%d\n",dp[V]);
	}
	return 0;
}
