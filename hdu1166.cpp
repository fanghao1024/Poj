#include<stdio.h>
#include<string.h>

typedef long long ll;
const int max_n=50010;
int N;
ll num[max_n];
ll tree[max_n<<2];
int lp(int p){return p<<1;}
int rp(int p){return (p<<1)|1;}

void push_up(int p){
	tree[p]=tree[lp(p)]+tree[rp(p)];
}
void build(int p,int pl,int pr){
	if(pl==pr){
		tree[p]=num[pl];
		return ;
	}
	int mid=(pl+pr)>>1;
	build(lp(p),pl,mid);
	build(rp(p),mid+1,pr);
	push_up(p);
}

void update(int x,ll d,int p,int pl,int pr){
	if(pr==pl&&pl==x){
		tree[p]+=d;
		tree[p]=tree[p]>0?tree[p]:0;
		return ;
	}
	int mid=(pl+pr)>>1;
	if(x<=mid) update(x,d,lp(p),pl,mid);
	if(x>mid) update(x,d,rp(p),mid+1,pr);
	push_up(p);
}
ll get_sum(int L,int R,int p,int pl,int pr){
	if(L<=pl&&pr<=R){
		return tree[p];
	}
	int mid=(pl+pr)>>1;
	ll res=0;
	if(L<=mid) res+=get_sum(L,R,lp(p),pl,mid);
	if(R>mid) res+=get_sum(L,R,rp(p),mid+1,pr);
	return res;
}
int main(){
	int T;
	scanf("%d",&T);
	for(int case_num=1;case_num<=T;case_num++){
		scanf("%d",&N);
		for(int i=1;i<=N;i++){
			scanf("%lld",&num[i]);
		}

		build(1,1,N);
		char ch[10];
		int x,y;
		ll d;
		printf("Case %d:\n",case_num);
		while(scanf("%s",ch)){
			if(ch[0]=='E'){
				break;
			}else{
				
				if(ch[0]=='Q'){
					scanf("%d %d",&x,&y);
					//for(int i=1;i<4*N;i++) printf("~~%lld ",tree[i]);
					//printf("\n");
					printf("%lld\n",get_sum(x,y,1,1,N));
				}else{
					if(ch[0]=='A'){
						scanf("%d %lld",&x,&d);
						update(x,d,1,1,N);
					}else{
						scanf("%d %lld",&x,&d);
						if(ch[0]=='S'){
							update(x,-d,1,1,N);
						}
					}
				}
			}
			
		}
	}
	return 0;
}
