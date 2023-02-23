#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=505;

int dp[max_n][max_n];
int a[max_n],b[max_n];
int N,M;
int path[max_n];
int marka[max_n],markb[max_n];
int fa[max_n][max_n],fb[max_n][max_n];
void Print(int n,int j){
	if(n>1){
		if(dp[n][j]==dp[n-1][j]) Print(n-1,j);
		else{
			int k;
			for(k=j-1;k>=1;k--) if(b[k]<b[j]&&dp[n-1][k]==dp[n][j]-1) break;
			Print(n-1,k);
			printf("%d ",b[j]);
		}
	}else if(dp[1][j]==1) printf("%d ",b[j]);
}
void solve(int* a,int n,int* b,int m){
	memset(dp,0,sizeof(dp));

	int ans=0;
	int ansx=-1,ansy=-1;
	int val_id=-1;
	int indexj=-1;
	for(int i=1;i<=n;i++){
		int val=0;
		for(int j=1;j<=m;j++){
			if(a[i]!=b[j]) dp[i][j]=dp[i-1][j];
			else{
				dp[i][j]=val+1;
				if(ans<dp[i][j]) ans=dp[i][j],indexj=j;
			}
			if(b[j]<a[i]){
				if(val<dp[i-1][j]) val=dp[i-1][j];
			}
		}
	}

	printf("%d\n",ans);
	Print(n,indexj);
	printf("\n");
}
int main(){
	while(scanf("%d",&N)!=EOF){
		for(int i=1;i<=N;i++) scanf("%d",a+i);
		scanf("%d",&M);
		for(int i=1;i<=M;i++) scanf("%d",b+i);
		solve(a,N,b,M);
	}
	return 0;
}
