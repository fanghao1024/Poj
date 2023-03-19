#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=25;
const int max_m=15010;
int dp[max_n][max_m];
int C,G;
int c[max_n],g[max_n];
int main(){
	while(scanf("%d %d",&C,&G)!=EOF){
		for(int i=1;i<=C;i++) scanf("%d",&c[i]);
		for(int i=1;i<=G;i++) scanf("%d",&g[i]);
		memset(dp,0,sizeof(dp));
		dp[0][7500]=1;
		for(int i=1;i<=G;i++){
			for(int j=0;j<=15000;j++){
				for(int k=1;k<=C;k++){
					if(j>=c[k]*g[i]) dp[i][j]+=dp[i-1][j-g[i]*c[k]];
				}
			}
		}
		printf("%d\n",dp[G][7500]);
	}
	return 0;
}

