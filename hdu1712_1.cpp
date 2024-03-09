#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;

int num[max_n][max_n];
int dp[max_n];

int N,M;

int main(){
	while(scanf("%d %d",&N,&M)&&(N+M)){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=M;j++){
				scanf("%d",&num[i][j]);
			}
		}
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=N;i++){
			for(int j=M;j>=1;j--){
				for(int k=1;k<=M;k++){
					if(j>=k) dp[j]=max(dp[j],dp[j-k]+num[i][k]);
				}
			}
		}
		printf("%d\n",dp[M]);
	}
	return 0;
}
