#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=5e5+10;

struct Tree{
	ll sum;
	int ma,mb,cnt,se;
	int tag1,tag2,tag3,tag4;
}tr[max_n<<2];
int N,M;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void push_up(int p){
	tr[p].ma=max(tr[ls(p)].ma,tr[rs(p)].ma);
	tr[p].mb=max(tr[ls(p)].mb,tr[rs(p)].mb);
	tr[p].sum=tr[ls(p)].sum+tr[rs(p)].sum;
	if(tr[ls(p)].ma==tr[rs(p)].ma){
		tr[p].cnt=tr[ls(p)].cnt+tr[rs(p)].cnt;
		tr[p].se=max(tr[ls(p)].se,tr[rs(p)].se);
	}
	else if(tr[ls(p)].ma>tr[rs(p)].ma){
		tr[p].cnt=tr[ls(p)].cnt;
		tr[p].se=max(tr[ls(p)].se,tr[rs(p)].ma);
	}
	else if(tr[ls(p)].ma<tr[rs(p)].ma){
		tr[p].cnt=tr[rs(p)].cnt;
		tr[p].se=max(tr[ls(p)].ma,tr[rs(p)].se);
	}
}
void build(int p,int pl,int pr){
	tr[p].tag1=tr[p].tag2=tr[p].tag3=tr[p].tag4=0;
	if(pl==pr){
		int x;
		//scanf("%d",&x);
		tr[p].sum=tr[p].ma=tr[p].mb=read();
		tr[p].se=-2e9;
		tr[p].cnt=1;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void change(int p,int pl,int pr,int k1,int k2,int k3,int k4){
	tr[p].sum+=1LL*k1*tr[p].cnt+1LL*k2*(pr-pl+1-tr[p].cnt);
	tr[p].mb=max(tr[p].mb,tr[p].ma+k3);
	tr[p].ma+=k1;
	if(tr[p].se!=-2e9) tr[p].se+=k2;
	tr[p].tag3=max(tr[p].tag3,tr[p].tag1+k3);
	tr[p].tag4=max(tr[p].tag4,tr[p].tag2+k4);
	tr[p].tag1+=k1;
	tr[p].tag2+=k2;
}
void push_down(int p,int pl,int pr){
	int Max=max(tr[ls(p)].ma,tr[rs(p)].ma);
	int mid=(pl+pr)>>1;
	if(tr[ls(p)].ma==Max){
		change(ls(p),pl,mid,tr[p].tag1,tr[p].tag2,tr[p].tag3,tr[p].tag4);
	}else change(ls(p),pl,mid,tr[p].tag2,tr[p].tag2,tr[p].tag4,tr[p].tag4);
	if(tr[rs(p)].ma==Max){
		change(rs(p),mid+1,pr,tr[p].tag1,tr[p].tag2,tr[p].tag3,tr[p].tag4);
	}else change(rs(p),mid+1,pr,tr[p].tag2,tr[p].tag2,tr[p].tag4,tr[p].tag4);
	tr[p].tag1=tr[p].tag2=tr[p].tag3=tr[p].tag4=0;
}
void update_add(int p,int pl,int pr,int L,int R,int k){
	if(L<=pl&&pr<=R){
		tr[p].sum+=1LL*k*(pr-pl+1);
		tr[p].ma+=k;
		tr[p].mb=max(tr[p].mb,tr[p].ma);
		if(tr[p].se!=-2e9) tr[p].se+=k;
		tr[p].tag1+=k;
		tr[p].tag3=max(tr[p].tag3,tr[p].tag1);
		tr[p].tag2+=k;
		tr[p].tag4=max(tr[p].tag4,tr[p].tag2);
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update_add(ls(p),pl,mid,L,R,k);
	if(R>mid) update_add(rs(p),mid+1,pr,L,R,k);
	push_up(p);
}
void update_min(int p,int pl,int pr,int L,int R,int v){
	if(v>tr[p].ma) return ;
	if(L<=pl&&pr<=R&&v>tr[p].se){
		int k=tr[p].ma-v;
		tr[p].sum-=1LL*k*tr[p].cnt;
		tr[p].ma=v;
		tr[p].tag1-=k;
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update_min(ls(p),pl,mid,L,R,v);
	if(R>mid) update_min(rs(p),mid+1,pr,L,R,v);
	push_up(p);
}
ll query_sum(int p,int pl,int pr,int L,int R){
	if(L<=pl&&pr<=R) return tr[p].sum;
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(R<=mid) return query_sum(ls(p),pl,mid,L,R);
	if(L>mid) return query_sum(rs(p),mid+1,pr,L,R);
	return query_sum(ls(p),pl,mid,L,mid)+query_sum(rs(p),mid+1,pr,mid+1,R);
}
int query_maxa(int p,int pl,int pr,int L,int R){
	if(L<=pl&&pr<=R) return tr[p].ma;
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(R<=mid) return query_maxa(ls(p),pl,mid,L,R);
	if(L>mid) return query_maxa(rs(p),mid+1,pr,L,R);
	return max(query_maxa(ls(p),pl,mid,L,mid),query_maxa(rs(p),mid+1,pr,mid+1,R));
}
int query_maxb(int p,int pl,int pr,int L,int R){
	if(L<=pl&&pr<=R) return tr[p].mb;
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(R<=mid) return query_maxb(ls(p),pl,mid,L,R);
	if(L>mid) return query_maxb(rs(p),mid+1,pr,L,R);
	return max(query_maxb(ls(p),pl,mid,L,mid),query_maxb(rs(p),mid+1,pr,mid+1,R));
}
int main(){
	//scanf("%d %d",&N,&M);
	N=read();M=read();
	build(1,1,N);
	int ops,l,r,v,k;
	while(M--){
		scanf("%d %d %d",&ops,&l,&r);
		switch (ops) {
		case 1:
			scanf("%d",&k);
			update_add(1,1,N,l,r,k);
			break;
		case 2:
			scanf("%d",&v);
			update_min(1,1,N,l,r,v);
			break;
		case 3:
			printf("%lld\n",query_sum(1,1,N,l,r));
			break;
		case 4:
			printf("%d\n",query_maxa(1,1,N,l,r));
			break;
		case 5:
			printf("%d\n",query_maxb(1,1,N,l,r));
			break;
		}
	}
	return 0;
}
