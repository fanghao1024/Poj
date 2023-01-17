#include<stdio.h>

typedef long long ll;
#define lowbit(x) x&(-x)
const int max_n=100010;
int N,M;
ll tree1[max_n],tree2[max_n];

void update1(int x,ll d){while(x<=N){tree1[x]+=d;x+=lowbit(x);}}
void update2(int x,ll d){while(x<=N){tree2[x]+=d;x+=lowbit(x);}}
ll sum1(int x){ll res=0;while(x>0){res+=tree1[x];x-=lowbit(x);}return res;}
ll sum2(int x){ll res=0;while(x>0){res+=tree2[x];x-=lowbit(x);}return res;}

int main(){
	scanf("%d %d",&N,&M);
	ll old=0,a;
	for(int i=1;i<=N;i++){
		scanf("%lld",&a);
		update1(i,a-old);
		update2(i,(i-1)*(a-old));
		old=a;
	}
	ll x,y,k;
	while(M--){
		scanf("%lld",&a);
		switch (a) {
		case 1:
			scanf("%lld %lld %lld",&x,&y,&k);
			update1(x,k);
			update1(y+1,-k);
			update2(x,(x-1)*k);
			update2(y+1,-y*k);
			break;
		case 2:
			scanf("%lld %lld",&x,&y);
			printf("%lld\n",y*sum1(y)-sum2(y)-(x-1)*sum1(x-1)+sum2(x-1));
			break;
		
		}
	}
	return 0;
}
