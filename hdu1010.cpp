#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=10;
char maze[max_n][max_n];
bool vis[max_n][max_n];
int N,M,T;
int sr,sc,er,ec;
bool flag;
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
void dfs(int x,int y,int time){
	if(flag) return ;
	if(maze[x][y]=='D'){
		if(time==T) flag=1;
		return ;
	}
	int temp=T-time-abs(er-x)-abs(ec-y);
	if(temp<0) return ;
	for(int i=0;i<4;i++){
		int nx=x+dir[i][0];
		int ny=y+dir[i][1];
		if(nx>=0&&nx<N&&ny>=0&&ny<M&&maze[nx][ny]!='X'&&!vis[nx][ny]){
			vis[nx][ny]=1;
			dfs(nx,ny,time+1);
			vis[nx][ny]=0;
		}
	}
	return ;
}
int main(){
	while(scanf("%d %d %d",&N,&M,&T)!=EOF){
		if(N==0&&M==0&&T==0) break;
		for(int i=0;i<N;i++){
			scanf("%s",maze[i]);
			for(int j=0;j<M;j++){
				if(maze[i][j]=='S'){
					sr=i;
					sc=j;
				}
				if(maze[i][j]=='D'){
					er=i;
					ec=j;
				}
			}
		}
		int temp=T-abs(er-sr)-abs(ec-sc);
		if(temp&1){printf("NO\n");continue;}
		memset(vis,0,sizeof(vis));
		flag=false;
		vis[sr][sc]=1;
		dfs(sr,sc,0);
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
