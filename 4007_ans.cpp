#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int M=500500;
int n,col=0,lim;
int map[10][10];
int vis[10][10],jud[10];
int fx[5]={0,0,1,-1},fy[5]={1,-1,0,0};
int check()
{
	int fuck=0;//统计剩余颜色
	fill(jud,jud+10,0);
	for (int i=1;i<=n;i++)
		for (int k=1;k<=n;k++)
			if (vis[i][k]!=1&&jud[map[i][k]]==0) fuck++,jud[map[i][k]]=1;//一种颜色统计一次
	return fuck;
}
void paint(int x,int y,int c)//染色
{
	vis[x][y]=1;
	for (int i=0;i<4;i++)
	{
		int xx=x+fx[i];
		int yy=y+fy[i];//四个方向
		if (xx<1||yy<1||xx>n||yy>n||vis[xx][yy]==1) continue;//越界
		if (map[xx][yy]==c) paint(xx,yy,c);//颜色相同继续扩展
		else vis[xx][yy]=2;//否则标记为待更新
	}
	return ;
}
bool orz(int qlm)//剪枝，步骤3
{
	int fuck=0;
	for (int i=1;i<=n;i++)
		for (int k=1;k<=n;k++)
			if (map[i][k]==qlm&&vis[i][k]==2)//待扩展点，与当前搜索颜色相同
				paint(i,k,qlm),fuck=1;//可以扩展，剪枝同时给图染色
	return fuck;//若没有扩展则返回零
}
bool IDAS(int limdep)
{
	if (limdep==lim) return !check();//搜索到限制深度，返回check，即图中是否省零个未染色点
	if(limdep+check()>lim) return 0;//剪枝，上面	
	for (int i=0;i<=5;i++)
	{
		int emm[10][10];
		memcpy(emm,vis,sizeof(vis));//注意sizeof里
		if (!orz(i)) continue;//剪枝
		if (IDAS(limdep+1)) return 1;//染色完成
		memcpy(vis,emm,sizeof(emm));//回溯
	}
	return 0;
}
int main()
{
	while (~scanf("%d",&n)&&n)
	{
		memset(vis,0,sizeof(vis));
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				scanf("%d",&map[i][j]);
		paint(1,1,map[1][1]);
		for (lim=check();;lim++) //从初始颜色个数开始，最少需要这么多步
			if (IDAS(0)) break;
		printf("%d\n",lim);
	}	
	return 0;
} 
