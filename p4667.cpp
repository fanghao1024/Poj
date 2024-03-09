#include<cstdio>
#include<cstring>
#include<algorithm>
#include<deque>
using namespace std;

const int max_n=510;
int dir[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
int ab[4]={2,1,1,2};
int cd[4][2]={{-1,-1},{-1,0},{0,-1},{0,0}};
int graph[max_n][max_n];
int dis[max_n][max_n];
bool vis[max_n][max_n];
int N,M;
char ch[max_n];
struct Point{
	int r,c;
	int d;
	Point(){};
	Point(int _r,int _c,int _d){
		r=_r;c=_c;d=_d;
	}
};
void bfs(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	deque<Point> deq;
	vis[1][1]=1;
	dis[1][1]=0;
	deq.push_back(Point(1,1,0));
	while(!deq.empty()){
		Point p=deq.front();
		deq.pop_front();
		if(p.r==N+1&&p.c==M+1) break;
		if(p.d>dis[p.r][p.c]) continue;
		for(int i=0;i<4;i++){
			int nr=p.r+dir[i][0];
			int nc=p.c+dir[i][1];
			int d=graph[p.r+cd[i][0]][p.c+cd[i][1]]!=ab[i];
			if(nr>0&&nr<=N+1&&nc>0&&nc<=M+1&&dis[nr][nc]>dis[p.r][p.c]+d){
				dis[nr][nc]=dis[p.r][p.c]+d;
				if(d==0) deq.push_front(Point(nr,nc,dis[nr][nc]));
				else deq.push_back(Point(nr,nc,dis[nr][nc]));
			}
		}
	}
	
}
int main(){
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++){
		scanf("%s",ch);
		for(int j=0;j<M;j++){
			graph[i][j+1]=ch[j]=='/'?1:2;
		}
	}
	bfs();
	if(dis[N+1][M+1]!=0x3f3f3f3f) printf("%d\n",dis[N+1][M+1]);
	else printf("NO SOLUTION\n");
	return 0;
}
