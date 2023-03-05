#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
char a[42][42];
int w,h;
int visit[42][42];
pair<int,int> s,e;
int m[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int pl;
int bfs()
{
	queue<pair<int,int> >q;
	while(!q.empty()) q.pop();
	q.push(s);
	memset(visit,0,sizeof(visit));
	visit[s.first][s.second]=1;
	while(!q.empty()){
		pair<int,int> now=q.front(); q.pop();
		for(int i=0;i<4;i++){
			int sx=now.first+m[i][0];
			int sy=now.second+m[i][1];
			if(0<=sx&&sx<h&&0<=sy&&sy<w&&visit[sx][sy]==0&&a[sx][sy]!='#'){
				visit[sx][sy]=visit[now.first][now.second]+1;
				q.push(make_pair(sx,sy));
			}
		}
		if(visit[e.first][e.second]!=0) break;
	}
	return visit[e.first][e.second];
}
int dfs(int x,int y,int pl,int foot,int t)
{
	for(int i=0;i<4;i++)
	{
		int temp=(pl+t-i*t+4)%4;
		int sx=x+m[temp][0];
		int sy=y+m[temp][1];
		if(a[sx][sy]=='E') return foot+1;
		if(a[sx][sy]=='.') return dfs(sx,sy,temp,foot+1,t);	
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&w,&h);
		for(int i=0;i<h;i++)
			scanf("%s",a[i]);
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++){
			if(a[i][j]=='S') {
				s.first=i; s.second=j;
			}
			if(a[i][j]=='E') {
				e.first=i; e.second=j;
			}
		}
		if(s.first==h-1) pl=2; 
		if(s.first==0) pl=0;
		if(s.second==0) pl=1;
		if(s.second==w-1) pl=3;
		printf("%d %d %d\n",dfs(s.first,s.second,pl,1,1),dfs(s.first,s.second,pl,1,-1),bfs()); 
		
	} 
}
