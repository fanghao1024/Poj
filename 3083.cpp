#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=43;

char ch[max_n][max_n];
bool vis[max_n][max_n];
int d[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
typedef pair<int,int> P;
int T,W,H;
int sx,sy,ex,ey;
queue<pair<P,int> > q;
int dfs(int x,int y,int pl,int foot,int t){
	for(int i=0;i<4;i++){
		
	}
}
int bfs(){
	memset(vis,0,sizeof(vis));
	vis[sx][sy]=1;
	while(!q.empty()) q.pop();
	q.push(make_pair(make_pair(sx,sy),1));
	int ans=1;
	while(!q.empty()){
		P pos=q.front().first;
		int dis=q.front().second;
		q.pop();
		int x=pos.first,y=pos.second;
		if(x==ex&&y==ey) return dis;
		
		for(int i=0;i<4;i++){
			int nx=x+d[0][i][0];
			int ny=y+d[0][i][1];
			if(nx>=0&&nx<W&&ny>=0&&ny<H)
			if(nx>=0&&nx<W&&ny>=0&&ny<H&&!vis[nx][ny]&&ch[ny][nx]!='#'){
				q.push(make_pair(make_pair(nx,ny),dis+1));
				vis[nx][ny]=1;
				
			}
		}
		
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&W,&H);
		for(int i=0;i<H;i++){
			scanf("%s",ch[i]);
			for(int j=0;j<W;j++){
				if(ch[i][j]=='S'){
					sx=j;
					sy=i;
				}
				if(ch[i][j]=='E'){
					ex=j;
					ey=i;
				}
			}
		}
		int direction;
		if(sy==H-1) direction=0;
		else if(sx==0) direction=1;
		else if(sy==0) direction=2;
		else direction=3;
		
		printf("%d",dfs(sx,sy,direction,0));
		if(sy==H-1) direction=0;
		else if(sx==W-1) direction=1;
		else if(sy==0) direction=2;
		else direction=3;
		//printf(" %d",dfs(sx,sy,direction,1));
		printf(" %d\n",bfs());
	}
	return 0;
}
