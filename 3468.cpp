#include<stdio.h>

typedef long long ll;
const int max_n=100010;
int N,Q;
ll num[max_n];
char ch[max_n];
ll A[max_n],B[max_n],C[max_n];

ll rec[max_n<<2],tag[max_n<<2];
ll ls(ll p){return p<<1;}
ll rs(ll p){return p<<1|1;}
void push_up(ll p){
	rec[p]=rec[ls(p)]+rec[rs(p)];
}
void build(ll p,ll pl,ll pr){
	tag[p]=0;
	if(pl==pr){
		rec[p]=num[pl];
		return ;
	}
	ll mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void addTag(ll p,ll pl,ll pr,ll d){
	tag[p]+=d;
	rec[p]+=(pr-pl+1)*d;
}
void push_down(ll p,ll pl,ll pr){
	if(tag[p]){
		ll mid=(pl+pr)>>1;
		addTag(ls(p),pl,mid,tag[p]);
		addTag(rs(p),mid+1,pr,tag[p]);
		tag[p]=0;
	}
}
void update(ll L,ll R,ll d,ll p,ll pl,ll pr){
	if(L<=pl&&pr<=R){
		addTag(p,pl,pr,d);
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update(L,R,d,ls(p),pl,mid);
	if(R>mid) update(L,R,d,rs(p),mid+1,pr);
	push_up(p);
}
ll query(ll L,ll R,ll p,ll pl,ll pr){
	if(L<=pl&&pr<=R) return rec[p];
	push_down(p,pl,pr);
	ll res=0;
	ll mid=(pl+pr)>>1;
	if(L<=mid) res+=query(L,R,ls(p),pl,mid);
	if(R>mid) res+=query(L,R,rs(p),mid+1,pr);
	return res;
}
int main(){
	scanf("%d %d",&N,&Q);
	for(int i=1;i<=N;i++){
		scanf("%lld",&num[i]);
	}
	for(int i=1;i<=Q;i++){
		scanf(" %c",&ch[i]);
		switch (ch[i]) {
		case 'Q':
			scanf("%lld %lld",&A[i],&B[i]);
			break;
		case 'C':
			scanf("%lld %lld %lld",&A[i],&B[i],&C[i]);
			break;
		}
	}
	build(1,1,N);

	for(int i=1;i<=Q;i++){
		switch (ch[i]) {
		case 'Q':
			printf("%lld\n",query(A[i],B[i],1,1,N));
			break;
		case 'C':
			update(A[i],B[i],C[i],1,1,N);
			break;
		}
	}
	
	return 0;
}
