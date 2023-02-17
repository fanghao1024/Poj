#include<cstdio>
#include<cstring>

const int max_n=105;
const int max_m=100010;
int N,M;
bool dp[max_m];
int num[max_m];
int A[max_n],C[max_n];
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		if(N==0&&M==0) break;
		for(int i=0;i<N;i++) scanf("%d",&A[i]);
		for(int i=0;i<N;i++) scanf("%d",&C[i]);
		memset(dp,0,sizeof(dp));
		dp[0]=1;
		int ans=0;
		for(int i=0;i<N;i++){
			memset(num,0,sizeof(num));
			for(int j=A[i];j<=M;j++){
				if(!dp[j]&&dp[j-A[i]]&&num[j-A[i]]<C[i]){
					dp[j]=1;
					num[j]=num[j-A[i]]+1;
					ans++;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
