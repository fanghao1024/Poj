#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef __int64 ll;

int T,N;
ll c[100010];
struct Num{
	int v;
	int id;
}num[100010];
bool cmp(const Num& a,const Num& b){
	return a.v<=b.v;
}
int lowbit(int x){return x&(-x);}
void add(int pos){
	while(pos<=N){
		c[pos]+=1LL;
		pos+=lowbit(pos);
	}
}
ll getsum(int n){
	ll res=0;
	while(n){
		res+=c[n];
		n-=lowbit(n);
	}
	return res;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		memset(c,0,sizeof(c));
		for(int i=1;i<=N;i++) scanf("%d",&num[i].v),num[i].id=i;
		sort(num+1,num+1+N,cmp);
		add(num[1].id);
		ll ans=0;
		ll lmax,lmin,rmax,rmin;
		for(int i=2;i<N;i++){
			lmin=getsum(num[i].id-1);
			rmin=getsum(N)-getsum(num[i].id);
			lmax=num[i].id-1-lmin;
			rmax=N-num[i].id-rmin;
			ans+=lmin*rmax+lmax*rmin;
			add(num[i].id);
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
