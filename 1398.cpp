#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
int dp[max_n][max_n];
int T,S,C;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&S,&C);
		for(int i=0;i<S;i++) scanf("%d",&dp[0][i]);
		for(int i=1;i<=S-1;i++){
			for(int j=0;j<S-i;j++){
				dp[i][j]=dp[i-1][j+1]-dp[i-1][j];
			}
		}
		for(int i=1;i<=C;i++) dp[S-1][i]=dp[S-1][i-1];
		for(int i=S-2;i>=0;i--){
			for(int j=0;j<C;j++){
				dp[i][S-i+j]=dp[i][S-i+j-1]+dp[i+1][S-i+j-1];
			}
		}
		for(int j=0;j<C;j++){
			if(j) printf(" ");
			printf("%d",dp[0][S+j]);
		}
		printf("\n");
	}
	return 0;
}
