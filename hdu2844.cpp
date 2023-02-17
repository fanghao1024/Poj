#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=105;
const int max_m=100010;
int N,M;
bool dp[max_m];
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
			if(A[i]*C[i]>=M){
				for(int j=A[i];j<=M;j++){
					if(dp[j-A[i]]) dp[j]=1;
				}
			}
			else{
				for(int k=1;C[i]>0;k<<=1){
					int x=min(k,C[i]);
					for(int j=M;j>=A[i]*x;j--){
						if(dp[j-A[i]*x]) dp[j]=1;
					}
					C[i]-=k;
				}
			}
		}
		for(int i=1;i<=M;i++) if(dp[i]) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
