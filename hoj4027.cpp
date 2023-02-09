#include <iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

typedef long long ll;
const int max_n=100010;
int N,M;
ll num[max_n];
ll tree[4*max_n];
int ls(int p){return p<<1;}
int rs(int p){return p<<1|1;}

void push_up(int p){
	tree[p]=tree[ls(p)]+tree[rs(p)];
}
void init(int p,int pl,int pr){
	if(pl==pr){
		tree[p]=num[pl];
		return ;
	}
	int mid=((pr-pl)>>1)+pl;
	init(ls(p),pl,mid);
	init(rs(p),mid+1,pr);
	push_up(p);
}

ll query(int L,int R,int p,int pl,int pr){
	if(L<=pl && pr<=R){
		return tree[p];
	}
	int mid=(pl+pr)>>1;
	ll res=0;
	if(L<=mid){
		res+=query(L,R,ls(p),pl,mid);
	}
	if(R>mid){
		res+=query(L,R,rs(p),mid+1,pr);
	}
	return res;
}

void update(int L,int R,int p,int pl,int pr){
	if(pl==pr){
		tree[p]=int(sqrt(tree[p]+0.0));
		return;
	}
	if(tree[p]==pr-pl+1) return;
	int mid=((pr-pl)>>1)+pl;
	if(L<=mid) update(L,R,ls(p),pl,mid);
	if(R>mid) update(L,R,rs(p),mid+1,pr);
	push_up(p);
}
int main() {
	int case_num=0;
	while(scanf("%d",&N)!=EOF){
		case_num++;
		for(int i=1;i<=N;i++){
			scanf("%lld",&num[i]);
		}
		
		init(1,1,N);
		scanf("%d",&M);
		
		printf("Case #%d:\n",case_num);
		int T,X,Y;
		while(M--){
			scanf("%d %d %d",&T,&X,&Y);
			if(X>Y) swap(X,Y);
			switch (T) {
				case 0:
					update(X,Y,1,1,N);
					break;
				case 1:
					printf("%lld\n",query(X, Y, 1, 1, N));
					break;
			}
		}
		printf("\n");
		
	}
		
	return 0;
}