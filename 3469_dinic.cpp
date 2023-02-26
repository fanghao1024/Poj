#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define Max 0x1fffffff
#define size 20100
struct edge{int from, to, val, next;}e[2000000];
int head[size], que[size], dis[size], cnt, cur[size];
void insert(int from, int to, int va)
{
	e[cnt].from = from;
	e[cnt].to = to; 
	e[cnt].val = va;
	e[cnt].next = head[from];
	head[from] = cnt++;
	
	e[cnt].from = to;
	e[cnt].to = from; 
	e[cnt].val = 0;
	e[cnt].next = head[to];
	head[to] = cnt++;
}

bool bfs(int s,int t){
	queue<int> q;
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=e[i].next){
			if(e[i].val>0&&dis[e[i].to]==-1){
				dis[e[i].to]=dis[u]+1;
				q.push(e[i].to);
				if(e[i].to==t) return true;
			}
		}
	}
	return false;
}

int Dinic(int n, int s, int t)
{
	int maxflow = 0, tmp, i;
	while(bfs(s, t))
	{
		int u = s, tail = 0;
		for(i = 0; i < n; i++) cur[i] = head[i];
		while(cur[s] != -1)
		{
			if (u != t && cur[u] != -1 && e[cur[u]].val > 0 && dis[u] != -1 && dis[u] + 1 == dis[e[cur[u]].to])
			{
				que[tail++] = cur[u]; 
				u = e[cur[u]].to;
			}
			else if (u == t)
			{
				for(tmp = Max, i = tail - 1; i >= 0; i--) tmp = min(tmp, e[que[i]].val);
				for(maxflow += tmp, i = tail - 1; i >= 0; i--)
				{
					e[que[i]].val -= tmp;
					e[que[i] ^ 1].val += tmp;
					if (e[que[i]].val == 0) tail = i;
				}
				u = e[que[tail]].from;
			}
			else
			{
				while(tail > 0 && u != s && cur[u] == -1) u = e[que[--tail]].from;
				cur[u] = e[cur[u]].next;
			}
		}	
	}
	return maxflow;
}
int n ,m, a, b, c;
int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		int s = 0, t = n + 1;
		memset(head, -1, sizeof(head)); 
		cnt = 0;
		for(int i = 1; i <= n; i++)
		{
			scanf("%d%d", &a, &b);
			insert(s, i, a); insert(i, t, b);
		}
		while(m-- && scanf("%d%d%d", &a, &b, &c)) insert(a, b, c), insert(b, a, c);
		printf("%d\n", Dinic(t + 1, s, t));
	}
	return 0;
}

