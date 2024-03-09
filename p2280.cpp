#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5100;
const int inf=0x3f3f3f3f;
int dp[max_n][max_n];
int N,M;
int x,y,v;

int main(){
	int ans=0;
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++){
		scanf("%d %d %d",&x,&y,&v);
		dp[x+1][y+1]=v;
	}
	for(int i=1;i<max_n;i++){
		for(int j=1;j<max_n;j++){
			dp[i][j]=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+dp[i][j];
		}
	}
	for(int i=0;i<max_n-M;i++){
		for(int j=0;j<max_n-M;j++){
			ans=max(ans,dp[i+M][j+M]-dp[i+M][j]-dp[i][j+M]+dp[i][j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
