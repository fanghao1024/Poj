#include<stdio.h>
#include<queue>
#include<cstring>
#include<map>
#include<stack>
using namespace std;

typedef pair<int,int> P;
int maze[10][10];
int prex[10][10];
int prey[10][10];
bool vis[10][10];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int path[30];
int main(){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			scanf("%d",&maze[i][j]);
		}
	}
	memset(prex,-1,sizeof(prex));
	memset(prey,-1,sizeof(prey));
	memset(vis,0,sizeof(vis));
	queue<P> q;
	q.push(make_pair(0,0));
	vis[0][0]=1;
	while(!q.empty())
	{
		P p=q.front();
		q.pop();
		if(p.first==4&&p.second==4) break;
		for(int i=0;i<4;i++){
			int x=p.first+dx[i];
			int y=p.second+dy[i];
			if(x>=0&&x<5&&y>=0&&y<5&&!maze[x][y]&&!vis[x][y]){
				vis[x][y]=1;
				q.push(make_pair(x,y));
				prex[x][y]=p.first;
				prey[x][y]=p.second;
			}
		}
	}
	int x=4;
	int y=4;
	stack<P> sp;
	while(prex[x][y]!=-1&&prey[x][y]!=-1){
		sp.push(make_pair(x,y));
		int tempx=x;
		int tempy=y;
		x=prex[tempx][tempy];
		y=prey[tempx][tempy];
	}
	printf("(0, 0)\n");
	while(!sp.empty()){
		printf("(%d, %d)\n",sp.top().first,sp.top().second);
		sp.pop();
	}
	return 0;
}
