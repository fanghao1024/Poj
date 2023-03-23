#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
const int N=5;
int map[10][10];//邻接矩阵
int screen[N][N];//屏幕最后显示的内容
string cover[N][N];//能覆盖(i,j)位置的窗口
string s;
int vis[10];//标记
int id[10];//入度
int t;//记录出现的窗口种类数

void cal()//初始化cover
{
	int k,i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			cover[i][j].erase();
	for(k=1;k<=9;k++)
	{
		i=(k-1)/3;
		j=(k-1)%3;
		cover[i][j]+=(char)(k);
		cover[i][j+1]+=(char)(k);
		cover[i+1][j]+=(char)(k);
		cover[i+1][j+1]+=(char)(k);
	}
}

void init()
{
	int i,j,k;
	memset(id,0,sizeof(id));
	memset(vis,0,sizeof(vis));
	memset(map,0,sizeof(map));
	t=0;
	for(i=0;i<N-1;i++)
	{
		for(j=0;j<N-1;j++)
		{
			scanf("%d",&k);
			if(!vis[k])
			{
				t++;
				vis[k]=1;
			}
			screen[i][j]=k;
		}
	}
}

void build()//构造有向图
{
	int i,j,k;
	for(i=0;i<N-1;i++)
	{
		for(j=0;j<N-1;j++)
		{
			for(k=0;k<cover[i][j].length();k++)
			{
				if((!map[screen[i][j]][cover[i][j][k]]) && (screen[i][j]!=cover[i][j][k]))
				{
					map[screen[i][j]][cover[i][j][k]]=1;
					id[cover[i][j][k]]++;
				}
			}
		}
	}
}

int topo()//拓扑排序，判环
{
	int i,j,k;
	for(i=0;i<t;i++)
	{
		k=1;
		while(!vis[k] || (k<=9&&id[k]>0))
			k++;
		if(k>9)
			return 0;
		vis[k]=0;
		for(j=1;j<10;j++)
		{
			if(vis[j]&&map[k][j])
				id[j]--;
		}
	}
	return 1;
}

int main()
{
	
	cal();
	while(cin>>s)
	{
		if(s=="ENDOFINPUT")
			break;
		init();
		build();
		if(topo())
			puts("THESE WINDOWS ARE CLEAN");
		else
			puts("THESE WINDOWS ARE BROKEN");
		cin>>s;
	}
	return 0;
}
