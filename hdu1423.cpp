#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=510;
int a[max_n],b[max_n];
int dp[max_n][max_n];
int T;
int N,M,ans;
void solve(int* a,int n,int *b,int m){
	memset(dp,0,sizeof(dp));
	ans=0;
	for(int i=1;i<=n;i++){
		int val=0;
		for(int j=1;j<=m;j++){
			
			if(a[i]!=b[j]) dp[i][j]=dp[i-1][j];
			else {dp[i][j]=val+1;ans=max(ans,dp[i][j]);}
			if(b[j]<a[i]) val=max(val,dp[i-1][j]);
		}
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=1;i<=N;i++){
			scanf("%d",a+i);
		}
		scanf("%d",&M);
		for(int i=1;i<=M;i++){
			scanf("%d",b+i);
		}
		solve(a,N,b,M);
		if(T) printf("\n");
	}
	return 0;
}

