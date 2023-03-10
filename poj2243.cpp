#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

int dir[8][2]={{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}};
int sr,sc,er,ec;
struct Point{
	int r,c;
	int step;
	int f;
	Point(){};
	Point(int _r,int _c,int _step){
		r=_r;c=_c;step=_step;f=_step+(abs(_r-er)+abs(_c-ec))*10;
	}
	bool operator<(const Point& a)const{
		return f>a.f;
		//return step>a.step;
	}
};
bool vis[30][30];
char s[5],e[5];
int ans;
bool check(int r,int c){
	if(r<1||r>8||c<1||c>8) return false;
	return true;
}
void bfs(){
	priority_queue<Point> pq;
	ans=0x3f3f3f3f;;
	memset(vis,0,sizeof(vis));
	pq.push(Point(sr,sc,0));
	vis[sr][sc]=1;
	while(!pq.empty()){
		Point p=pq.top();
		pq.pop();
		
		if(p.r==er&&p.c==ec){ans=min(ans,p.step);break;};
		if(p.step>ans) continue;
		for(int i=0;i<8;i++){
			int nr=p.r+dir[i][0];
			int nc=p.c+dir[i][1];
			if(check(nr,nc)&&!vis[nr][nc]){
				pq.push(Point(nr,nc,p.step+1));
				vis[nr][nc]=1;
			}
		}
	}
	
}
int main(){
	while(scanf("%s %s",s,e)!=EOF){
		sc=s[0]-'a'+1;
		sr=s[1]-'0';
		ec=e[0]-'a'+1;
		er=e[1]-'0';
		bfs();
		printf("To get from %s to %s takes %d knight moves.\n",s,e,ans);
	}
	return 0;
}
