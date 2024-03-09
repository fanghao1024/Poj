#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

int n;//地图大小 
int timex[200][200];//转弯次数记录 
int cachex,cachey,sx,sy,ex,ey;//起点，终点坐标和队首坐标缓存 
int wayx[4]={-1,0,1,0},wayy[4]={0,1,0,-1};//方向表 
queue<int>quex,quey;
char mapx[200][200]={0};//地图 
bool teller[4]={true};//扩展层数判断 

int main()
{
	memset(timex,-1,sizeof(timex));
	cin>>n;
	for (int i=0;i<n;i++) 
		for (int j=0;j<n;j++) 
	{
		cin>>mapx[i][j];
		if (mapx[i][j]=='A'){sx=i;sy=j;}//记录起点 
		if (mapx[i][j]=='B'){ex=i;ey=j;mapx[i][j]='.';}//记录终点并且让终点可以入队 
	}
	//cout<<sx<<" "<<sy<<" "<<ex<<" "<<ey<<" "<<endl; /*去掉注释可以看起点终点的位置*/ 
	quex.push(sx); quey.push(sy); 
	while (quex.size()>0)
	{
		memset(teller,true,sizeof(teller));//初始化 扩展层数判断变量 
		cachex=quex.front(); cachey=quey.front();//缓存存入 
		if (cachex==ex && cachey==ey)//如果到了终点，输出（这个题不存在起点=终点的情况，因为分别用AB表示 
		{
			cout<<timex[ex][ey]<<endl;
			return 0;
		}
		for (int j=0;j<=3;j++)//四个方向 
		{
			for (int i=1;i<=n;i++)/*开一层*/ 
				if (teller[j]==true) /*如果该方向上 前面一层没遇到障碍*/ 
			{
				//cout<<"Direction= "<<j<<" Now Position At: "<<cachex+wayx[j]*i<<" "<<cachey+wayy[j]*i<<endl; /*去掉注释看方向、现在扩展到的位置坐标 */ 
				if (cachex+wayx[j]*i>=0 && cachex+wayx[j]*i<n && cachey+wayy[j]*i>=0 && cachey+wayy[j]*i<n)//越界判断 
				{
					if (mapx[cachex+wayx[j]*i][cachey+wayy[j]*i]=='.' && timex[cachex+wayx[j]*i][cachey+wayy[j]*i]==-1) //未被访问且不是障碍 
					{
						timex[cachex+wayx[j]*i][cachey+wayy[j]*i]=timex[cachex][cachey]+1;//计算转弯次数 
						quex.push(cachex+wayx[j]*i); quey.push(cachey+wayy[j]*i);//入队列 
					}
					else if (mapx[cachex+wayx[j]*i][cachey+wayy[j]*i]=='x') teller[j]=false;//此方向该层存在障碍，结束此方向的扩展 
				}
				else teller[j]=false;//越界，结束扩展 
			}
		}
		//showTimex(); /*去掉注释可以看每一次扩展完之后的转弯次数表*/ 
		quex.pop(); quey.pop();//队首元素出队 
	}
	cout<<-1<<endl;//搜完全图，没搜到 
	return 0;
}
