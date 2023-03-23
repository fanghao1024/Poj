#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;

int indeg[12],tot;
int vis[10];
int graph[10][10];
string cover[4][4];
void calc()//计算出当前方格可能被几号窗口覆盖的可能性
{
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			cover[i][j].erase();
	for(int k=1; k<=9; k++)
	{
		int i=(k-1)/3;
		int j=(k-1)%3;
		cover[i][j]+=char(k+'0');
		cover[i][j+1]+=char(k+'0');
		cover[i+1][j]+=char(k+'0');
		cover[i+1][j+1]+=char(k+'0');
	}
}


int num[4][4],ans;
char ops[20];
void inits(){
	memset(indeg,0,sizeof(indeg));
	memset(vis,0,sizeof(vis));
	memset(graph,0,sizeof(graph));
	tot=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			scanf("%d",&num[i][j]);
			if(!vis[num[i][j]]){
				tot++;
				vis[num[i][j]]=1;
			}
		}
	}
}
void init()
{
	int k;
	memset(vis,0,sizeof(vis));
	memset(indeg,0,sizeof(indeg));
	memset(graph,0,sizeof(graph));
	tot=0;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
	{
		scanf("%d",&k);
		num[i][j]=k;
		if(!vis[k]) tot++;//记录出现的屏幕种类数
		vis[k]=1;
	}
}

void builds(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			for(int p=0; p<cover[i][j].length(); p++){
				int x=num[i][j];
				int y=cover[i][j][p]-'0';
				if(!graph[x][y]&&x!=y){
					graph[x][y]=1;
					indeg[y]++;
				}
			}
		}
	}
}
void build()//建图
{
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int p=0; p<cover[i][j].length(); p++)
	{
		int x=num[i][j];
		int y=cover[i][j][p]-'0';
		if(!graph[x][y]&&x!=y)//当前x->y没有边，且x和y不是同一条边
		{
			graph[x][y]=1;
			indeg[y]++;
		}
	}
}
int check()
{
	int i,j,k;
	for(k=0; k<tot; k++)
	{
		i=1;
		while(!vis[i]||(i<=9&&indeg[i]>0)) //排除入度大于0的
			i++;
		if(i>9)//大于数字9证明死机了
			return 0;
		vis[i]=0;
		for(j=1; j<=9; j++)
			if(vis[j]&&graph[i][j])
				indeg[j]--;//对入度减一
	}
	return 1;
}

bool checks(){
	bool flag=true;
	for(int i=0;i<tot;i++){
		int j=1;
		while(!vis[j]||(j<=9&&indeg[j]>0)) j++;
		if(j>9){
			flag=false;
			break;
		}
		vis[j]=0;
		//topsort(j);
		for(int z=1;z<=9;z++){
			if(vis[z]&&graph[j][z]) indeg[z]--;
		}
	}
	return flag;
}
int main(){
	calc();
	while(scanf("%s",ops)!=EOF){
		if(strlen(ops)>5) break;
		init();
		build();
		if(check()) printf("THESE WINDOWS ARE CLEAN\n");
		else printf("THESE WINDOWS ARE BROKEN\n");
		scanf("%s",ops);
	}
	return 0;
}
