#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e4+10;

int N,M,cnt;
int tree[max_n<<2],pre[max_n<<2],suf[max_n<<2];
int history[max_n];
inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}
void push_up(int p,int len){
	pre[p]=pre[ls(p)];
	suf[p]=suf[rs(p)];
	if(pre[ls(p)]==len-(len>>1)) pre[p]=pre[ls(p)]+pre[rs(p)];
	if(suf[rs(p)]==(len>>1)) suf[p]=suf[ls(p)]+suf[rs(p)];
}
void build(int p,int pl,int pr){
	if(pl==pr){
		tree[p]=pre[p]=suf[p]=1;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p,pr-pl+1);
}
int query(int p,int pl,int pr,int x){
	if(pl==pr) return tree[p];
	int mid=(pl+pr)>>1;
	if(x<=mid){
		if(x+suf[ls(p)]>mid){
			return suf[ls(p)]+pre[rs(p)];
		}else{
			return query(ls(p),pl,mid,x);
		}
	}else{
		if(mid+pre[rs(p)]>=x) return suf[ls(p)]+pre[rs(p)];
		else return query(rs(p),mid+1,pr,x);
	}
}
void update(int p,int pl,int pr,int x,int d){
	if(pl==pr){
		tree[p]=pre[p]=suf[p]=d;
		return ;
	}
	int mid=(pl+pr)>>1;
	if(x<=mid) update(ls(p),pl,mid,x,d);
	else update(rs(p),mid+1,pr,x,d);
	push_up(p,pr-pl+1);
}
int main(){
	scanf("%d %d",&N,&M);
	build(1,1,N);
	cnt=0;
	char ch[3];
	int x;
	while(M--){
		while(scanf("%s",ch)!=EOF){
		if(ch[0]=='Q'){
			scanf("%d",&x);
			printf("%d\n",query(1,1,N,x));
		}
		else if(ch[0]=='D'){
			scanf("%d",&x);
			history[cnt++]=x;
			update(1,1,N,x,0);
		}
		else{
			x=history[--cnt];
			update(1,1,N,x,1);
		}
	}
	}
	return 0;
}
