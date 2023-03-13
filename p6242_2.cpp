#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=5e5+10;

int N,M;
struct Tree{
	ll sum;
	int ma,mb,se,cnt;
	int tag1,tag2,tag3,tag4;
}tr[max_n<<2];

inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}

int read(){
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num*=10;
		num+=ch-'0';
		ch=getchar();
	}
	return num*f;
}
inline void push_up(int p){
	tr[p].sum=tr[ls(p)].sum+tr[rs(p)].sum;
	tr[p].ma=max(tr[ls(p)].ma,tr[rs(p)].ma);
	tr[p].mb=max(tr[ls(p)].mb,tr[rs(p)].mb);
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
inline void build(int p,int pl,int pr){
	tr[p].tag1=tr[p].tag2=tr[p].tag3=tr[p].tag4=0;
	if(pl==pr){
		tr[p].sum=tr[p].ma=tr[p].mb=read();
		tr[p].cnt=1;
		tr[p].se=-2e9;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
inline void change(int p,int pl,int pr,int t1,int t2,int t3,int t4){
	tr[p].sum+=1LL*t1*tr[p].cnt+1LL*t2*(pr-pl+1-tr[p].cnt);
	tr[p].mb=max(tr[p].mb,tr[p].ma+t3);
	tr[p].ma+=t1;
	if(tr[p].se!=-2e9) tr[p].se+=t2;
	tr[p].tag3=max(tr[p].tag3,tr[p].tag1+t3);
	tr[p].tag4=max(tr[p].tag4,tr[p].tag2+t4);
	tr[p].tag1+=t1;
	tr[p].tag2+=t2;
}
inline void push_down(int p,int pl,int pr){
	int Max=max(tr[ls(p)].ma,tr[rs(p)].ma);
	int mid=(pl+pr)>>1;
	if(tr[ls(p)].ma==Max) change(ls(p),pl,mid,tr[p].tag1,tr[p].tag2,tr[p].tag3,tr[p].tag4);
	else change(ls(p),pl,mid,tr[p].tag2,tr[p].tag2,tr[p].tag4,tr[p].tag4);
	if(tr[rs(p)].ma==Max) change(rs(p),mid+1,pr,tr[p].tag1,tr[p].tag2,tr[p].tag3,tr[p].tag4);
	else change(rs(p),mid+1,pr,tr[p].tag2,tr[p].tag2,tr[p].tag4,tr[p].tag4);
	tr[p].tag1=tr[p].tag2=tr[p].tag3=tr[p].tag4=0;
}
void update_add(int p,int pl,int pr,int l,int r,int k){
	if(l<=pl&&pr<=r){
		tr[p].sum+=1LL*k*(pr-pl+1);
		tr[p].ma+=k;
		if(tr[p].se!=-2e9) tr[p].se+=k;
		tr[p].mb=max(tr[p].mb,tr[p].ma);
		tr[p].tag1+=k;tr[p].tag2+=k;
		tr[p].tag3=max(tr[p].tag3,tr[p].tag1);
		tr[p].tag4=max(tr[p].tag4,tr[p].tag2);
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(l<=mid) update_add(ls(p),pl,mid,l,r,k);
	if(r>mid) update_add(rs(p),mid+1,pr,l,r,k);
	push_up(p);
}
void update_min(int p,int pl,int pr,int l,int r,int v){
	if(v>tr[p].ma) return ;
	if(l<=pl&&pr<=r&&v>tr[p].se){
		int temp=tr[p].ma-v;
		tr[p].sum-=1LL*temp*tr[p].cnt;
		tr[p].ma=v;
		tr[p].tag1-=temp;
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(l<=mid) update_min(ls(p),pl,mid,l,r,v);
	if(r>mid) update_min(rs(p),mid+1,pr,l,r,v);
	push_up(p);
}
ll query_sum(int p,int pl,int pr,int l,int r){
	if(l<=pl&&pr<=r) return tr[p].sum;
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(r<=mid) return query_sum(ls(p),pl,mid,l,r);
	if(l>mid) return query_sum(rs(p),mid+1,pr,l,r);
	return query_sum(ls(p),pl,mid,l,mid)+query_sum(rs(p),mid+1,pr,mid+1,r);
}
int query_maxa(int p,int pl,int pr,int l,int r){
	if(l<=pl&&pr<=r) return tr[p].ma;
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(r<=mid) return query_maxa(ls(p),pl,mid,l,r);
	if(l>mid) return query_maxa(rs(p),mid+1,pr,l,r);
	return max(query_maxa(ls(p),pl,mid,l,mid),query_maxa(rs(p),mid+1,pr,mid+1,r));
}
int query_maxb(int p,int pl,int pr,int l,int r){
	if(l<=pl&&pr<=r) return tr[p].mb;
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(r<=mid) return query_maxb(ls(p),pl,mid,l,r);
	if(l>mid) return query_maxb(rs(p),mid+1,pr,l,r);
	return max(query_maxb(ls(p),pl,mid,l,mid),query_maxb(rs(p),mid+1,pr,mid+1,r));
}
int main(){
	N=read();M=read();
	build(1,1,N);
	int ops,l,r,k,v;
	while(M--){
		ops=read();l=read();r=read();
		switch (ops) {
		case 1:
			k=read();
			update_add(1,1,N,l,r,k);
			break;
		case 2:
			v=read();
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
