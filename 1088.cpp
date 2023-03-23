#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=105;
int mat[max_n][max_n];
int dp[max_n][max_n];
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int R,C;
int dfs(int r,int c){
	if(dp[r][c]!=-1) return dp[r][c];
	int res=0;
	for(int i=0;i<4;i++){
		int nr=r+dir[i][0],nc=c+dir[i][1];
		if(nr>=1&&nr<=R&&nc>=1&&nc<=C){
			if(mat[r][c]>mat[nr][nc]) res=max(res,dfs(nr,nc));
		}
	}
	dp[r][c]=res+1;
	return dp[r][c];
}
int main(){
	scanf("%d %d",&R,&C);
	for(int i=1;i<=R;i++){
		for(int j=1;j<=C;j++){
			scanf("%d",&mat[i][j]);
		}
	}
	memset(dp,-1,sizeof(dp));
	int ans=0;
	for(int i=1;i<=R;i++){
		for(int j=1;j<=C;j++){
			ans=max(ans,dfs(i,j));
		}
	}
	printf("%d\n",ans);
	return 0;
}
