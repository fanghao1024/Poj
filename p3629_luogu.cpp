#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
using namespace std;
int n,k,root1,root2,cir,cir2;
int cur,head[100010],d[100010],heavy[100010],w[100010];
struct tedge
{
	int to,nex;
}e[200010];
struct Data
{
	int e,v;
}son[100010];
void Add(int u,int v)
{
	cur++;
	e[cur].to = v;
	e[cur].nex = head[u];
	head[u] = cur;
}
bool cmp(Data a,Data b)
{
	return a.e>b.e;
}
void dfs(int u,int f)
{
	int cnts=0;
	for (int i=head[u]; i!=-1; i=e[i].nex)
	{
		int v=e[i].to;
		if (v==f) continue;
		dfs(v,u);
		if (d[u]<d[v]+w[v]) 
		{
			d[u] = d[v]+w[v];
			heavy[u] = v;
		}
	}
	for (int i=head[u]; i!=-1; i=e[i].nex)
	{
		int v=e[i].to;
		if (v==f) continue;
		cnts++;  son[cnts].e = d[v]+w[v];  son[cnts].v = v;
	}
	sort(son+1,son+1+cnts,cmp);
	if (cnts==0) d[u] = 0;
	if (cnts>=1&&cir<son[1].e) 
	{
		cir = son[1].e;
		root1 = son[1].v;
	}
	if (cnts>=2&&cir<son[1].e+son[2].e)
	{
		cir = son[1].e+son[2].e;
		root1 = son[1].v;  root2 = son[2].v;
	}
}
void Change()
{
	int u = root1;
	while (u!=0)
	{
		w[u] = -1;  u = heavy[u];
	}
	u = root2;
	while (u!=0)
	{
		w[u] = -1;  u = heavy[u];
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=0; i<=n; i++)
		head[i] = -1;
	for (int i=2; i<=n; i++)
		w[i] = 1;
	for (int i=1; i<n; i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Add(x,y);  Add(y,x);
	}
	cir = 0;
	dfs(1,0);
	if (k==1)
	{
		printf("%d\n",2*(n-1)-cir+1);
		return 0;
	}
	Change();
	cir2 = cir;  cir = -1e9;
	for (int i=1; i<=n; i++)
		d[i] = -1e9;
	dfs(1,0);
	printf("%d\n",2*(n-1)-cir-cir2+2);
	return 0;
}
