#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

typedef long long ll;
const int max_n=310;

int W,H;
int rec[max_n][max_n];
bool vis[max_n][max_n];
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
struct Node{
	int r,c;
	int h;
	Node(){};
	Node(int _r,int _c,int _h){
		r=_r;c=_c;h=_h;
	}
	bool operator<(const Node& m) const{
		return h>m.h;
	}
};
priority_queue<Node> q;
bool check(int i,int j){
	if(i<0||i>=H||j<0||j>=W) return false;
	return true;
}

int main(){
	while(scanf("%d %d",&W,&H)!=EOF){
		for(int i=0;i<H;i++){
			for(int j=0;j<W;j++)
				scanf("%d",&rec[i][j]);
		}
		while(!q.empty()) q.pop();
		memset(vis,0,sizeof(vis));
		for(int i=0;i<W;i++){
			q.push(Node(0,i,rec[0][i]));vis[0][i]=1;
			q.push(Node(H-1,i,rec[H-1][i]));vis[H-1][i]=1;
		}	
		for(int i=1;i<H-1;i++){
			q.push(Node(i,0,rec[i][0]));vis[i][0]=1;
			q.push(Node(i,W-1,rec[i][W-1]));vis[i][W-1]=1;
		}
		ll ans=0;
		while(!q.empty()){
			Node u=q.top();
			q.pop();
			int r=u.r,c=u.c,h=u.h;
			for(int i=0;i<4;i++){
				int nr=r+dir[i][0];
				int nc=c+dir[i][1];
				if(check(nr,nc)&&!vis[nr][nc]){
					vis[nr][nc]=1;
					if(rec[nr][nc]>=h){
						q.push(Node(nr,nc,rec[nr][nc]));
						
					}else{
						ans+=h-rec[nr][nc];
						rec[nr][nc]=h;
						q.push(Node(nr,nc,h));
					}
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
