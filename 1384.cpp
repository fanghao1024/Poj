#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_w=10010;
const int max_n=505;
const int inf=0x3f3f3f3f;
int dp[max_w];
int P[max_n],W[max_n];
int T,E,F,N;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&E,&F);
		int Weight=F-E;
		memset(dp,0x3f,sizeof(dp));
		scanf("%d",&N);
		for(int i=0;i<N;i++) scanf("%d %d",&P[i],&W[i]);
		dp[0]=0;
		for(int i=0;i<N;i++){
			for(int j=W[i];j<=Weight;j++){
				dp[j]=min(dp[j],dp[j-W[i]]+P[i]);	
			}
		}
		if(dp[Weight]!=inf){
			printf("The minimum amount of money in the piggy-bank is %d.\n",dp[Weight]);
		}else{
			printf("This is impossible.\n");
		}
	}
	return 0;
}
