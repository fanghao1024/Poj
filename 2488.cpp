#include<stdio.h>
#include<string.h>
#include<string>
using namespace std;

const int max_n=30;
bool vis[max_n][max_n];
int row[max_n];
int col[max_n];
int N;
int p,q;
int dx[8]={-1,1,-2,2,-2,2,-1,1};
int dy[8]={-2,-2,-1,-1,1,1,2,2};
bool dfs(int x,int y,int dep,int row[],int col[]){
	vis[x][y]=1;
	row[dep]=x;
	col[dep]=y;
	if(dep==p*q){
		return true;
	}
	
	for(int i=0;i<8;i++){
		int cx=x+dx[i];
		int cy=y+dy[i];
		if(cx>=0&&cx<p&&cy>=0&&cy<q&&!vis[cx][cy]){
			if(dfs(cx,cy,dep+1,row,col)){
				return true;
			}
		}
	}
	vis[x][y]=0;
	return false;
}
int main(){
	scanf("%d",&N);
	
	for(int case_num=1;case_num<=N;case_num++){
		scanf("%d %d",&p,&q);
		printf("Scenario #%d:\n",case_num);
		memset(vis,0,sizeof(vis));
		string s="";
		if(dfs(0,0,1,row,col)){
			for(int i=1;i<=p*q;i++){
				printf("%c",'A'+col[i]);
				printf("%d",row[i]+1);
			}
			printf("\n\n");
		}else{
			printf("impossible\n\n");
		}
		
	}
	return 0;
}
