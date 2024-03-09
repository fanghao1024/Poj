#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=510;
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int N,M;
int rec[max_n][max_n],L[max_n][max_n],R[max_n][max_n];
bool vis[max_n][max_n];
bool check(int r,int c){
	if(r<1||r>N||c<1||c>M) return false;
	return true;
}
void dfs(int r,int c){
	vis[r][c]=1;
	for(int i=0;i<4;i++){
		int nr=r+dir[i][0];
		int nc=c+dir[i][1];
		if(check(nr,nc)&&rec[nr][nc]<rec[r][c]){
			if(!vis[nr][nc]) dfs(nr,nc);
			L[r][c]=min(L[r][c],L[nr][nc]);
			R[r][c]=max(R[r][c],R[nr][nc]);
		}
	}
}
int main(){
	scanf("%d %d",&N,&M);
	memset(L,0x3f,sizeof(L));
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			scanf("%d",&rec[i][j]);
			if(i==N) L[i][j]=R[i][j]=j;
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=M;i++){
		if(!vis[1][i]) dfs(1,i);
	}
	int ans=0;
	for(int i=1;i<=M;i++){
		if(!vis[N][i]) ans++;
	}
	if(ans){
		printf("0\n%d\n",ans);
	}else{
		ans=0;
		int left=1,right=R[1][1];
		while(left<=M){
			for(int i=1;i<=M;i++){
				if(L[1][i]<=left){
					right=max(right,R[1][i]);
				}
			}
			left=right+1;
			ans++;
		}
		printf("1\n%d\n",ans);
	}
	return 0;
}
