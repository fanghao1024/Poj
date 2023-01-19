#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>
using namespace std;

struct Pos{
	int x,y;
	int dep;
	Pos(){};
	Pos(int x,int y,int d){
		this->x=x;
		this->y=y;
		this->dep=d;
	}
};
queue<Pos> pq;
int L;
int sx,sy;
int ex,ey;
const int max_n=305;
bool vis[max_n][max_n];
int dx[]={1,2,2,1,-1,-2,-2,-1};
int dy[]={2,1,-1,-2,2,1,-1,-2};
int main(){
	int N;
	scanf("%d",&N);
	while(N--){
		while(!pq.empty()) pq.pop();
		scanf("%d",&L);
		scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
		memset(vis,0,sizeof(vis));
		pq.push(Pos(sx,sy,0));
		vis[sx][sy]=1;
		bool flag=false;
		while(!pq.empty()){
			Pos p=pq.front();
			pq.pop();
			int x=p.x;
			int y=p.y;
			int d=p.dep;
			if(x==ex&&y==ey){
				printf("%d\n",d);
				flag=true;
				break;
			}
			for(int i=0;i<8;i++){
				int nx=x+dx[i];
				int ny=y+dy[i];
				if(nx>=0&&nx<L&&ny>=0&&ny<L&&!vis[nx][ny]){
					if(nx==ex&&ny==ey){
						flag=true;
						printf("%d\n",d+1);
						break;
					}
					vis[nx][ny]=1;
					pq.push(Pos(nx,ny,d+1));
				}
			}
			if(flag) break;
			
		}
	}
	return 0;
}
