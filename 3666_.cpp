#include<stdio.h>
#include<algorithm>
using namespace std;

int dp[2010][2010];
int A[2010];
int B[2010];

const int inf=0x3fffffff;

int main(){
	int N;
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%d",&A[i]);
		B[i]=A[i];

	}
	sort(B+1,B+1+N);
	fill(dp[0],dp[0]+2010*2010,0);
	for(int i=1;i<=N;i++){
		int min_value=inf;
		for(int j=1;j<=N;j++){
			min_value=min(min_value,dp[i-1][j]);
			dp[i][j]=abs(A[i]-B[j])+min_value;
		}
	}
	int min_value=inf;
	for(int i=1;i<=N;i++){
		min_value=min(min_value,dp[N][i]);
	}
	printf("%d\n",min_value);
	return 0;
}
