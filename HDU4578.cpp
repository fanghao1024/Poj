#include <iostream>
#include<stdio.h>
using namespace std;

typedef long long ll;
const int max_n=100010;
const ll MOD=10007;
int N,M;
int ls(int x){return x<<1;}
int rs(int x){return (x<<1)|1;}
struct Node{
	ll sum1,sum2,sum3;
	ll mark1,mark2;
}node[max_n<<2];

void init(int p,int pl,int pr){
	node[p].sum1=node[p].sum2=node[p].sum3=node[p].mark2=0;
	node[p].mark1=1;
	if(pl==pr){
		return ;
	}
	int mid=((pr-pl)>>1)+pl;
	init(ls(p),pl,mid);
	init(rs(p),mid+1,pr);
	
}
void calc2(int mark1,int mark2,int p,int pl,int pr){
	int lens=pr-pl+1;
	node[p].sum3=((mark1*mark1*mark1%MOD)*node[p].sum3%MOD+(mark2*mark2*mark2%MOD)*lens%MOD+3ll*(mark1*mark1*mark2%MOD)*node[p].sum2%MOD+3ll*node[p].sum1*(mark1*mark2*mark2)%MOD)%MOD;
	node[p].sum2=(node[p].sum2*mark1*mark1%MOD+mark2*mark2*lens%MOD+2ll*mark1*mark2*node[p].sum1%MOD)%MOD;
	node[p].sum1=(node[p].sum1*mark1+mark2*lens)%MOD;
	
	node[p].mark1=(node[p].mark1*mark1)%MOD;
	node[p].mark2=(node[p].mark2*mark1+mark2)%MOD;
}
void calc(ll x,ll b,int rt,int pl,int pr){
	int len=pr-pl+1;
	node[rt].sum3=(((x*x*x)%MOD*node[rt].sum3)%MOD+((b*b*b)%MOD*len)%MOD+((3ll*x*b*b)%MOD*node[rt].sum1)%MOD+((3ll*x*x*b)%MOD*node[rt].sum2)%MOD)%MOD;
	node[rt].sum2=((x*x*node[rt].sum2)%MOD+(2ll*x*b*node[rt].sum1)%MOD+(b*b*len)%MOD)%MOD;
	node[rt].sum1=((x*node[rt].sum1)%MOD+b*len%MOD)%MOD;
	node[rt].mark1=(node[rt].mark1*x)%MOD;
	node[rt].mark2=(node[rt].mark2*x+b)%MOD;
}
void spread(int p,int pl,int pr){
	if(node[p].mark1!=1||node[p].mark2){
		int mid=(pl+pr)>>1;
		calc(node[p].mark1,node[p].mark2,ls(p),pl,mid);
		calc(node[p].mark1,node[p].mark2,rs(p),mid+1,pr);
		node[p].mark1=1;
		node[p].mark2=0;
	}
}
void update(int L,int R,int multip,int addi,int p,int pl,int pr){
	if(L<=pl&&pr<=R){
		calc(multip,addi,p,pl,pr);
		return ;
	}
	spread(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update(L, R, multip, addi, ls(p), pl, mid);
	if(R>mid) update(L,R,multip,addi,rs(p),mid+1,pr);
	node[p].sum1=(node[ls(p)].sum1+node[rs(p)].sum1)%MOD;
	node[p].sum2=(node[ls(p)].sum2+node[rs(p)].sum2)%MOD;
	node[p].sum3=(node[ls(p)].sum3+node[rs(p)].sum3)%MOD;
}

ll query(int L,int R,int C,int p,int pl,int pr){
	if(L<=pl&&pr<=R){
		switch (C) {
			case 1:
				return node[p].sum1;
			case 2:
				return node[p].sum2;
			case 3:
				return node[p].sum3;
		}
	}
	int mid=(pl+pr)>>1;
	spread(p,pl,pr);
	ll ans=0;
	if(L<=mid){
		ans=(ans+query(L,R,C,ls(p),pl,mid))%MOD;
	}
	if(R>mid){
		ans=(ans+query(L,R,C,rs(p),mid+1,pr))%MOD;
	}
	return ans;
}

int main() {
	while(scanf("%d %d",&N,&M)&&N&&M){
		init(1,1,N);
		int O,X,Y,C;
		while(M--){
			scanf("%d %d %d %d",&O,&X,&Y,&C);
			switch (O) {
				case 1:
					update(X,Y,1,C,1,1,N);
					break;
				case 2:
					update(X,Y,C,0,1,1,N);
					break;
				case 3:
					update(X,Y,0,C,1,1,N);
					break;
				case 4:
					printf("%lld\n",query(X,Y,C,1,1,N)%MOD);
					break;
			}
		}
	}
	
	return 0;
}