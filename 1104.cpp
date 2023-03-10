#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

struct Point{
	int pos[4][2];
	int d;
	Point(){};
	Point(int _x1,int _y1,int _x2,int _y2,int _x3,int _y3,int _x4,int _y4){
		pos[0][0]=_x1;pos[0][1]=_y1;pos[1][0]=_x2;pos[1][1]=_y2;pos[2][0]=_x3;pos[2][1]=_y3;pos[3][0]=_x4;pos[3][1]=_y4;
	}
}p[2];
struct Node{
	int x,y;
}node[4];;
bool cmp(const Node& a,const Node& b){
	if(a.x!=b.x) return a.x<b.x;
	else return a.y<b.y;
}
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
bool check(int r,int c){
	if(r<=0||r>8||c<=0||c>8) return false;
	return true;
}
char ch[9][9][9][9][9][9][9][9];
typedef pair<Point,int> P;
char getPos(Point p){
	for(int i=0;i<4;i++){
		node[i].x=p.pos[i][0];
		node[i].y=p.pos[i][1];
	}
	sort(node,node+4,cmp);
	return ch[node[0].x][node[0].y][node[1].x][node[1].y][node[2].x][node[2].y][node[3].x][node[3].y];
}
void setPos(Point p,int val){
	for(int i=0;i<4;i++){
		node[i].x=p.pos[i][0];
		node[i].y=p.pos[i][1];
	}
	sort(node,node+4,cmp);
	ch[node[0].x][node[0].y][node[1].x][node[1].y][node[2].x][node[2].y][node[3].x][node[3].y]=val;
}
queue<Point> q;
bool dbfs(){
	while(!q.empty()) q.pop();
	int len=0;
	p[0].d=1;
	p[1].d=-1;
	q.push(p[0]);
	q.push(p[1]);
	int cnt=0;
	while(!q.empty()){
		Point p=q.front();
		int d=p.d;
		q.pop();
		int m=getPos(p);
		if(d>0&&m==2){
			return true;		
		}
		if(d<0&&m==1) return true;
		
		if(m==0){
			if(d>0) setPos(p,1);
			else setPos(p,2);
		}
		
		if(d>=5||d<=-5) continue;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				int nx=p.pos[i][0]+dir[j][0];
				int ny=p.pos[i][1]+dir[j][1];
				bool flag=false;
				while(check(nx,ny)){
					flag=true;
					for(int k=0;k<4;k++){
						if(k!=i){
							if(p.pos[k][0]==nx&&p.pos[k][1]==ny){
								flag=false;
								break;
							}
						}
					}
					if(!flag){
						nx+=dir[j][0];
						ny+=dir[j][1];
					}
					else break;
				}
				if(!flag) continue;
				Point pp;
				for(int k=0;k<4;k++){
					if(k!=i){
						pp.pos[k][0]=p.pos[k][0];
						pp.pos[k][1]=p.pos[k][1];
					}else{
						pp.pos[k][0]=nx;
						pp.pos[k][1]=ny;
					}
				}
				pp.d=d>0?d+1:d-1;
				if((getPos(pp)!=2&&d<0)||(getPos(pp)!=1&&d>0)) 
					q.push(pp);
			}
		}
	}
	return false;
}
int main(){
	int x,y;
	
	while(scanf("%d%d%d%d%d%d%d%d",&p[0].pos[0][0],&p[0].pos[0][1],&p[0].pos[1][0],&p[0].pos[1][1],&p[0].pos[2][0],&p[0].pos[2][1],&p[0].pos[3][0],&p[0].pos[3][1])!=EOF){
	scanf("%d%d%d%d%d%d%d%d",&p[1].pos[0][0],&p[1].pos[0][1],&p[1].pos[1][0],&p[1].pos[1][1],&p[1].pos[2][0],&p[1].pos[2][1],&p[1].pos[3][0],&p[1].pos[3][1]);
	memset(ch,0,sizeof(ch));


	//ch[p[0].pos[0][0]][p[0].pos[0][1]][p[0].pos[1][0]][p[0].pos[1][1]][p[0].pos[2][0]][p[0].pos[2][1]][p[0].pos[3][0]][p[0].pos[3][1]]=1;
	//ch[p[1].pos[0][0]][p[1].pos[0][1]][p[1].pos[1][0]][p[1].pos[1][1]][p[1].pos[2][0]][p[1].pos[2][1]][p[1].pos[3][0]][p[1].pos[3][1]]=1;
	if(dbfs()) printf("YES\n");
	else printf("NO\n");
	}
	return 0;
}


