#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn=60000;

vector<int> fact[maxn];

void get_factor()
{
	for(int i=1;i<maxn;i++)
	{
		for(int j=i;j<maxn;j+=i)
		{
			fact[j].push_back(i);
		}
	}
}

int n,Q,T,tree[maxn],pre[maxn],arr[maxn],ans[maxn];

struct ASK
{
	int l,r,id;
}ask[maxn];

bool cmp(ASK a,ASK b)
{
	if(a.r!=b.r) return a.r<b.r;
	return a.l<b.l;
}

int lowbit(int x)
{
	return x&(-x);
}

void update(int p,int v) ///向下更新最大约数
{
	for(int i=p;i;i-=lowbit(i)) tree[i]=max(tree[i],v);
}

int query(int p)
{
	int ret=0;
	for(int i=p;i<maxn;i+=lowbit(i)) ret=max(ret,tree[i]);
	return ret;
}

int main()
{
	scanf("%d",&T);
	get_factor();
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",arr+i);
		scanf("%d",&Q);
		for(int i=0;i<Q;i++)
		{
			scanf("%d%d",&ask[i].l,&ask[i].r); ask[i].id=i;
		}
		sort(ask,ask+Q,cmp);
		memset(tree,0,sizeof(tree));
		memset(pre,-1,sizeof(pre));
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			for(int sz=fact[arr[i]].size(),j=0;j<sz;j++)
			{
				int fc=fact[arr[i]][j];
				if(pre[fc]!=-1)
				{
					update(pre[fc],fc);
				}
				pre[fc]=i;
			}
			while(cnt<Q&&ask[cnt].r==i)
			{
				ans[ask[cnt].id]=query(ask[cnt].l);
				cnt++;
			}
		}
		for(int i=0;i<Q;i++) printf("%d\n",ans[i]);
	}
	return 0;
}
