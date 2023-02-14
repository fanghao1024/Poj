#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=100005;
int N,M;
struct Linked_Cut_Tree{
	int fa[max_n],rev[max_n],son[max_n][2],dis[max_n],st[max_n],v[max_n],top;
	void init(){
		memset(fa,0,sizeof(fa));
		memset(rev,0,sizeof(rev));
		memset(son,0,sizeof(son));
		memset(dis,0,sizeof(dis));
		memset(v,0,sizeof(v));
	}
	void update(int x){
		dis[x]=dis[son[x][0]]+dis[son[x][1]]+v[x];
	}
	void pushdown(int x){
		if(rev[x]){
			rev[x]^=1;
			swap(son[x][0],son[x][1]);
			if(son[x][0]) rev[son[x][0]]^=1;
			if(son[x][1]) rev[son[x][1]]^=1;
		}
	}
	bool isroot(int x) {return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;}
	void rotate(int x){
		int f=fa[x],g=fa[f];
		int c=son[f][0]==x;
		son[f][!c]=son[x][c];
		fa[son[x][c]]=f;
		fa[x]=g;
		if(!isroot(f)) son[g][son[g][1]==f]=x;
		fa[f]=x;
		son[x][c]=f;
		update(f);update(x);
	}
	void splay(int x){
		st[top=1]=x;
		for(int i=x;!isroot(i);i=fa[i]) st[++top]=fa[i];
		while(top) pushdown(st[top--]);
		while(!isroot(x)){
			int f=fa[x],g=fa[f];
			if(!isroot(f)) (son[g][0]==f)^(son[f][0]==x)?rotate(x):rotate(f);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;x=fa[y=x]){
			splay(x);
			son[x][1]=y;
			update(x);
		}
	}
	void makeroot(int x){
		access(x);splay(x);rev[x]^=1;
	}
	void link(int x,int y){
		makeroot(x);
		fa[x]=y;
	}
	void split(int x,int y){
		makeroot(x);
		access(y);
		splay(y);
	}
}LCT;
int main(){
	int x,y,d;
	char ch;
	while(scanf("%d %d",&N,&M)!=EOF){
		LCT.init();
		for(int i=1;i<=M;i++){
			scanf("%d %d %d %c",&x,&y,&d,&ch);
			LCT.v[N+i]=d;
			LCT.link(x,N+i);
			LCT.link(N+i,y);
		}
		scanf("%d",&d);
		while(d--){
			scanf("%d %d",&x,&y);
			LCT.split(x,y);
			printf("%d\n",LCT.dis[y]);
		}
	}
	
	return 0;
}
