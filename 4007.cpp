#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;


const int max_n=10;
int a[max_n][max_n],vis[max_n][max_n];
int N,dep;
bool used[max_n],flag;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
bool check(){
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(a[i][j]!=a[1][1]) return false;
		}
	}
	return true;
}
void paint(int r,int c,int color){
	vis[r][c]=1;
	for(int i=0;i<4;i++){
		int nr=r+dir[i][0];
		int nc=c+dir[i][1];
		if(nr<1||nr>N||nc<1||nc>N||vis[nr][nc]==1) continue;
		if(a[nr][nc]==color){
			paint(nr,nc,color);
		}else{
			vis[nr][nc]=2;
		}
		
	}
}
void paints(int x,int y,int c)//染色
{
	vis[x][y]=1;
	for (int i=0;i<4;i++)
	{
		int xx=x+dir[i][0];
		int yy=y+dir[i][1];//四个方向
		if (xx<1||yy<1||xx>N||yy>N||vis[xx][yy]==1) continue;//越界
		if (a[xx][yy]==c) paints(xx,yy,c);//颜色相同继续扩展
		else vis[xx][yy]=2;//否则标记为待更新
	}
	return ;
}
int h(){
	memset(used,0,sizeof(used));
	int cnt=0;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(vis[i][j]!=1&&!used[a[i][j]]){
				used[a[i][j]]=1;
				cnt++;	
			}
		}
	}
	return cnt;
}
bool ok(int color){
	bool mark=false;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(a[i][j]==color&&vis[i][j]==2){
				paint(i,j,color);
				mark=true;
			}
		}
	}
	return mark;
}
bool ida(int d){
	if(!h()){
		printf("%d\n",d);
		return true;
	}
	if(d>=dep) return false;
	if(d+h()>dep) return false;
	int b[10][10];
	memcpy(b,vis,sizeof(vis));
	for(int i=0;i<6;i++){
		if(!ok(i)) continue;
		if(ida(d+1)) return true;
		memcpy(vis,b,sizeof(b));
	}
	return false;
}

int main(){
	while(scanf("%d",&N)&&N){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				scanf("%d",&a[i][j]);
			}
		}
		memset(vis,0,sizeof(vis));
		paint(1,1,a[1][1]);
		dep=h();
		while(1){
			if(ida(0)) break;
			dep++;
		}
		
	}
	return 0;
}
