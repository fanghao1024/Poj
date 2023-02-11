#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=100010;
int N,M;
int rec[max_n];
struct Linked_Cut_Tree{
	int v[max_n],fa[max_n],son[max_n][2],st[max_n],rev[max_n],top;
	void update(int x){
		v[x]=v[son[x][0]]^v[son[x][1]]^rec[x];
	}
	void pushdown(int x){
		if(rev[x]){	
			rev[x]^=1;
			swap(son[x][0],son[x][1]);
			if(son[x][0]) rev[son[x][0]]^=1;
			if(son[x][1]) rev[son[x][1]]^=1;
		}
	}
	bool isroot(int x){return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;}
	void rotate(int x){
		int f=fa[x],g=fa[f];
		int c=(son[f][0]==x);
		son[f][!c]=son[x][c];
		fa[son[x][c]]=f;
		fa[x]=g;
		if(!isroot(f)) son[g][son[g][1]==f]=x;
		fa[f]=x;
		son[x][c]=f;
		update(f);
		update(x);
	}
	void splay(int x){
		st[top=1]=x;
		for(int i=x;!isroot(i);i=fa[i]) st[++top]=fa[i];
		while(top) pushdown(st[top--]);
		while(!isroot(x)){
			int f=fa[x],g=fa[f];
			if(!isroot(f)) (son[f][0]==x)^(son[g][0]==f)?rotate(x):rotate(f);
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
	int findroot(int x){
		access(x);splay(x);
		while(son[x][0]) x=son[x][0];
		return x;
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
	void cut(int x,int y){
		split(x,y);
		if(son[y][0]==x&&!son[x][1]){
			son[y][0]=fa[son[y][0]]=0;
			update(y);
		}
	}
}LCT;
int main(){
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++){
		scanf("%d",&rec[i]);
		LCT.v[i]=rec[i];
	}
	int ops,x,y;
	while(M--){
		scanf("%d %d %d",&ops,&x,&y);
		switch (ops) {
		case 0:
			LCT.split(x,y);
			printf("%d\n",LCT.v[y]);
			break;
		case 1:
			if(LCT.findroot(x)!=LCT.findroot(y)){
				LCT.link(x,y);
			}
			break;
		case 2:
			if(LCT.findroot(x)==LCT.findroot(y)){
				LCT.cut(x,y);
			}
			break;
		case 3:
			LCT.splay(x);
			rec[x]=y;
			LCT.update(x);
			break;
		}
	}
	return 0;
}
