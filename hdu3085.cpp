#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
using namespace std;

const int max_n=805;
char maze[max_n][max_n];
bool xmvis[max_n][max_n];
bool gvis[max_n][max_n];
bool danger[max_n][max_n];
int N,M;
int gost[2][2];
int mx,my;
int gx,gy;
struct xiaoming{
	int x,y;
	int order;
	xiaoming(int _x,int _y,int _order){
		x=_x;
		y=_y;
		order=_order;
	}
};
struct girl{
	int x,y;
	int order;
	girl(int _x,int _y,int _order){
		x=_x;
		y=_y;
		order=_order;
	}
};
struct gosts{
	int x,y;
	int order;
	gosts(int _x,int _y,int _order){
		x=_x;
		y=_y;
		order=_order;
	}
};
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int bfs(){
	memset(xmvis,0,sizeof(xmvis));
	memset(gvis,0,sizeof(gvis));
	memset(danger,0,sizeof(danger));
	queue<xiaoming> qxm;
	queue<girl> qgf;
	queue<gosts> qg;
	qxm.push(xiaoming(mx,my,0));
	xmvis[mx][my]=1;
	qgf.push(girl(gx,gy,0));
	gvis[gx][gy]=1;
	for(int i=0;i<2;i++){
		qg.push(gosts(gost[i][0],gost[i][1],0));
		danger[gost[i][0]][gost[i][1]]=1;
	}
	int count=1;
	while(!qg.empty()&&!qgf.empty()&&!qxm.empty()){
		while(!qg.empty()&&qg.front().order<2*count){
			gosts g=qg.front();
			qg.pop();
			for(int i=0;i<4;i++){
				int x=g.x+dx[i];
				int y=g.y+dy[i];
				if(x>=0&&x<N&&y>=0&&y<M&&!danger[x][y]){
					danger[x][y]=1;
					qg.push(gosts(x,y,g.order+1));
				}
			}
		}
		while(!qxm.empty()&&qxm.front().order<3*count){
			xiaoming point=qxm.front();
			qxm.pop();
			if(danger[point.x][point.y]) continue;
			if(gvis[point.x][point.y]){
				return count;
			}
			for(int i=0;i<4;i++){
				int x=point.x+dx[i];
				int y=point.y+dy[i];
				if(x>=0&&x<N&&y>=0&&y<M&&maze[x][y]!='X'&&!danger[x][y]&&!xmvis[x][y]){
					if(gvis[x][y]){
						return count;
					}
					qxm.push(xiaoming(x,y,point.order+1));
					xmvis[x][y]=1;
				}
			}
		}
		while(!qgf.empty()&&qgf.front().order<count){
			girl point=qgf.front();
			qgf.pop();
			if(danger[point.x][point.y]) continue;
			if(xmvis[point.x][point.y]){
				return count;
			}
			for(int i=0;i<4;i++){
				int x=point.x+dx[i];
				int y=point.y+dy[i];
				if(x>=0&&x<N&&y>=0&&y<M&&maze[x][y]!='X'&&!danger[x][y]&&!gvis[x][y]){
					if(xmvis[x][y]){
						return count;
					}
					qgf.push(girl(x,y,point.order+1));
					gvis[x][y]=1;
				}
			}
		}
		count++;
	}
	return -1;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&N,&M);
		int count=0;
		for(int i=0;i<N;i++){
			scanf("%s",maze[i]);
			for(int j=0;j<M;j++){
				if(maze[i][j]=='Z'){
					gost[count][0]=i;
					gost[count][1]=j;
					count++;
				}
				if(maze[i][j]=='M'){
					mx=i;
					my=j;
				}
				if(maze[i][j]=='G'){
					gx=i;
					gy=j;
				}
			}
		}
		int ans=bfs();
		printf("%d\n",ans);
		
	}
	return 0;
}
