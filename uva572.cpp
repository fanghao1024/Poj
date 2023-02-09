#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

const int max_n=105;
char ch[max_n][max_n];
int M,N;
bool vis[max_n][max_n];
int dx[8]={-1,0,1,0,-1,-1,1,1};
int dy[8]={0,1,0,-1,-1,1,-1,1};
void dfs(int x,int y){
	vis[x][y]=1;
	for(int i=0;i<8
		;i++){
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(nx>=0&&nx<M&&ny>=0&&ny<N&&ch[nx][ny]=='@'&&!vis[nx][ny]){
			dfs(nx,ny);
		}
	}
}
int main() {
	while(scanf("%d %d",&M,&N)&&M){
		for(int i=0;i<M;i++){
			for(int j=0;j<N;j++){
				scanf(" %c",&ch[i][j]);
			}
		}
		memset(vis,0,sizeof(vis));
		int ans=0;
		for(int i=0;i<M;i++){
			for(int j=0;j<N;j++){
				if(ch[i][j]=='@'&&!vis[i][j]){
					ans++;
					dfs(i,j);
				}
			}
			
		}
		printf("%d\n",ans);
	}
	return 0;
}