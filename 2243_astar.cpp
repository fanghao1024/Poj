#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

const int maxn = 10;

struct Node{
	int x,y,step;
	int f,g,h;
	// g函数为走到当前状态的经过的步数，启发函数h为当前格子到终点横坐标差与纵坐标差的和，用优先队列保存每个状态按照g+h排序
	bool operator < (const Node & tmp) const{
		return f > tmp.f;
	}
}node;

bool visd[maxn][maxn];
priority_queue<Node> Que;
int dirs[8][2]={{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}};
int start_x,start_y,end_x,end_y,ans;

bool isIN(int x,int y)
{
	if(x>=8||x<0)return false;
	if(y>=8||y<0)return false;
	return true;
}
void init()
{
	memset(visd,false,sizeof(visd));
	while(!Que.empty())Que.pop();
	Node S;
	S.x=start_x;S.y=start_y;
	S.step=0;S.g=0;S.h=(abs(end_x-start_x)+abs(end_y-start_y))*10;
	S.f=S.g+S.h;
	visd[S.x][S.y]=true;
	Que.push(S);
	ans=-1;
}

void Astar()
{
	Node A,B;
	while(!Que.empty())
	{
		A=Que.top();Que.pop();
		if(A.x==end_x&&A.y==end_y)
		{
			ans=A.step;
			break;
		}
		for(int i=0;i<8;i++)
		{
			int xx=dirs[i][0]+A.x;
			int yy=dirs[i][1]+A.y;
			if(isIN(xx,yy)==false||visd[xx][yy])continue;
			B.x=xx;B.y=yy;
			B.step=A.step+1;
			B.g=A.g+23;
			B.h=(abs(end_y-yy)+abs(end_x-xx))*10;
			B.f=B.g+B.h;
			visd[B.x][B.y]=true;
			Que.push(B);
		}
	}
}

int main()
{
	char line[10];
	while(gets(line))
	{
		start_x=line[0]-'a';start_y=line[1]-'1';
		end_x=line[3]-'a';end_y=line[4]-'1';
		init();
		Astar();
		printf("To get from %c%c to %c%c takes %d knight moves.\n",line[0],line[1],line[3],line[4],ans);
	}
	
	return 0;
}
