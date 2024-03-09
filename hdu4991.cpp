#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=10010;
const int max_m=105;

int dp[max_n][max_m];

int N,M;
int num[max_n];
int main(){
	while(scanf("%d%d",&N,&M)!=EOF){
		for(int i=1;i<=N;i++) scanf("%d",&num[i]);
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=N;i++) dp[i][1]=1;
		for(int i=1;i<=N;i++){
			int val=0;
			for(int j=2;j<=M;j++){
				for(int k=1;k<i;k++){
					if(num[k]<num[i]) dp[i][j]+=dp[k][j-1];
				}
			}
		}
		int ans=0;
		for(int i=1;i<=N;i++) ans+=dp[i][M];
		printf("%d\n",ans);
	}
	return 0;
}
