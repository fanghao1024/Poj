#include<stdio.h>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int dp[2010][2010];
int A[2010];
const int inf=0x3fffffff;
int main(){
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%d",&A[i]);
	}

	
	
	fill(dp[0],dp[0]+2010*2010,inf);
	for(int i=0;i<N;i++){
		dp[i][i]=0;
		if(i<N-1){
			dp[i][i+1]=0;
		}
	}
	for(int l=3;l<=N;l++){
		for(int i=0;i<N-l+1;i++){
			int j=i+l-1;
			if((A[i]<=A[i+1]&&A[i+1]<=A[j])||(A[i]>=A[i+1]&&A[i+1]>=A[j])){
				dp[i][j]=min(dp[i][j],dp[i+1][j]);
			}
			if((A[j]>=A[j-1]&&A[j-1]>=A[i])||(A[j]<=A[j-1]&&A[j-1]<=A[i])){
				dp[i][j]=min(dp[i][j],dp[i][j-1]);
			}
			if(A[i]>A[i+1]&&A[i+1]<=A[j]){
				int cost=0;
				for(int k=i+1;k<=j;k++){
					if(A[i]>A[k]){
						cost+=abs(A[i]-A[k]);
					}else{
						break;
					}
				}
				cost=min(cost,abs(A[i]-A[i+1]));
				dp[i][j]=min(dp[i][j],dp[i+1][j]+cost);
			}
			if(A[i]<A[i+1]&&A[i+1]>=A[j]){
				int cost=0;
				for(int k=i+1;k<=j;k++){
					if(A[i]<A[k]){
						cost+=abs(A[i]-A[k]);
					}else{
						break;
					}
				}
				cost=min(cost,abs(A[i]-A[i+1]));
				dp[i][j]=min(dp[i][j],dp[i+1][j]+cost);
			}
			if(A[j]>A[j-1]&&A[i+1]>=A[j]){
				int cost=0;
				for(int k=j-1;k>=i;k--){
					if(A[j]>A[k]){
						cost+=abs(A[i]-A[k]);
					}else{
						break;
					}
				}
				cost=min(cost,abs(A[j]-A[j-1]));
				dp[i][j]=min(dp[i][j],dp[i][j-1]+cost);
			}
			if(A[j]<A[j-1]&&A[i]<=A[j]){
				int cost=0;
				for(int k=j-1;k>=i;k--){
					if(A[j]<A[k]){
						cost+=abs(A[i]-A[k]);
					}else{
						break;
					}
				}
				cost=min(cost,abs(A[j]-A[j-1]));
				dp[i][j]=min(dp[i][j],dp[i][j-1]+cost);
			}
			
		}
	}
	printf("%d\n",dp[0][N-1]);
	return 0;
}
