#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

typedef pair<int,int> P;
const int max_n=600;
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int T,R,C,cnt,o,ans;
char ch[max_n][max_n];
int pos[max_n][max_n],par[max_n];
bool vis[max_n][max_n];
struct Edge{
	int l,r;
	int dis;
}edge[max_n*max_n];
bool check(int i,int j){
	if(i<0||i>=R||j<0||j>=C) return false;
	return true;
}
void bfs(int r,int c){
	memset(vis,0,sizeof(vis));
	queue<pair<P,int> > q;
	q.push(make_pair(make_pair(r,c),0));
	vis[r][c]=1;
	while(!q.empty()){
		P p=q.front().first;
		int d=q.front().second;
		q.pop();
		for(int i=0;i<4;i++){
			int xr=p.first+dir[i][0];
			int yc=p.second+dir[i][1];
			if(check(xr,yc)&&ch[xr][yc]!='#'&&!vis[xr][yc]){
				q.push(make_pair(make_pair(xr,yc),d+1));
				vis[xr][yc]=1;
				if(ch[xr][yc]!=' '){
					edge[o].l=pos[r][c];
					edge[o].r=pos[xr][yc];
					edge[o].dis=d+1;
					o++;
				}
			}
		}
	}
}
bool cmp(const Edge& a,const Edge& b){
	return a.dis<b.dis;
}
void init(int n){
	for(int i=1;i<=cnt;i++){
		par[i]=i;
	}
}
int find(int x){
	if(x!=par[x]){
		par[x]=find(par[x]);
	}
	return par[x];
}
void unite(int x,int y){
	int a=find(x);
	int b=find(y);
	if(a!=b){
		par[a]=b;
	}
}
bool same(int x,int y){
	return find(x)==find(y);
}
void solve(){
	sort(edge,edge+o,cmp);
	init(cnt);
	for(int i=0;i<o;i++){
		if(!same(edge[i].l,edge[i].r)){
			unite(edge[i].l,edge[i].r);
			ans+=edge[i].dis;
		}
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&C,&R);
		gets(ch[0]);
		cnt=o=0;
		for(int i=0;i<R;i++) gets(ch[i]);
		for(int i=0;i<R;i++){
			for(int j=0;j<C;j++){
				if(ch[i][j]=='S'||ch[i][j]=='A') pos[i][j]=++cnt;
			}
		}
		if(cnt<=1){
			printf("0\n");
			continue;
		}
		for(int i=0;i<R;i++){
			for(int j=0;j<C;j++){
				if(ch[i][j]=='S'||ch[i][j]=='A') bfs(i,j);
			}
		}
		ans=0;
		solve();
		printf("%d\n",ans);
	}
	return 0;
}

