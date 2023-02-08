#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long ll;
int N;
int ls(int p){return p<<1;}
int rs(int p){return (p<<1)|1;}
const int max_n=100010;
ll tree[max_n<<2],tag[max_n<<2];
ll num[max_n];

void push_up(int p){
	//tree[p]=max(tree[ls(p)],tree[rs(p)]);
	if(tree[ls(p)]==tree[rs(p)]){
		tree[p]=tree[ls(p)];
	}else{
		tree[p]=-1;
	}
}

void build(int p,int pl,int pr){
	
	if(pl==pr){
		//tree[p]=num[pl];
		tag[p]=-1;
		return ;
	}	
	int mid=(pl+pr)/2;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	//push_up(p);
	tag[p]=-1;
}

void push_down(int p){
	if(tag[p]!=-1){
		tree[ls(p)]=tree[rs(p)]=tree[p];
		tag[ls(p)]=tag[rs(p)]=1;
		tag[p]=-1;
	}
}
void update1(int L,int R,ll d,int p,int pl,int pr){

	if(pr<L||pl>R) return;
	if(L<=pl&&pr<=R){
		//printf("===%d %d\n",pl,pr);
		tree[p]=d;
		tag[p]=1;
		return ;
	}
	push_down(p);
	int mid=(pl+pr)/2;
	if(L<=mid) update1(L,R,d,ls(p),pl,mid);
	if(R>mid) update1(L,R,d,rs(p),mid+1,pr);
	push_up(p);
}
ll gcd(ll a,ll b){
	if(b==0){
		return a;
	}else{
		return gcd(b,a%b);
	}
}
void update2(int L,int R,ll d,int p,int pl,int pr){
	if(tree[p]<=d) return;
	if(L<=pl&&pr<=R&&tree[p]!=-1){
		if(tree[p]>d){
			tree[p]=gcd(tree[p],d);
			tag[p]=1;
		}
			
		return;
	}
	push_down(p);
	int mid=(pl+pr)>>1;
	if(L<=mid) update2(L,R,d,ls(p),pl,mid);
	if(R>mid) update2(L,R,d,rs(p),mid+1,pr);
	push_up(p);
}
void print(int p,int pl,int pr){
	if(pl==pr){
		printf("%lld ",tree[p]);
		return;
	}
	push_down(p);
	int mid=(pl+pr)>>1;
	print(ls(p),pl,mid);
	print(rs(p),mid+1,pr);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		build(1,1,N);
		for(int i=1;i<=N;i++){
			scanf("%lld",num+i);
			update1(i,i,num[i],1,1,N);
		} 
		
		int Q;
		scanf("%d",&Q);
		int t,l,r;
		ll x;
		while(Q--){
			scanf("%d %d %d %lld",&t,&l,&r,&x);
			if(t==1){
				update1(l,r,x,1,1,N);
			}else{
				update2(l,r,x,1,1,N);
			}
		}
		print(1,1,N);
	}
	return 0;
}
