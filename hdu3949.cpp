#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;

const int max_n=1e4+10;
ll num[max_n];
int T,N,Q;
bool zero;
void Gauss(){
	int i,k=1;
	ll j=(ll)1<<62;
	for(;j>0;j>>=1){
		for(i=k;i<=N;i++){
			if(num[i]&j) break;
		}
		if(i>N) continue;
		swap(num[i],num[k]);
		for(i=1;i<=N;i++){
			if(i!=k&&num[i]&j) num[i]^=num[k];
		}
		k++;
	}
	k--;
	if(k!=N) zero=true;
	else zero=false;
	N=k;
}
ll query(ll x){
	ll res=0;
	if(zero) x--;
	if(!x) return 0;
	for(int i=N;i;i--){
		if(x&1) res^=num[i];
		x>>=1;
	}
	if(x) return -1;
	else return res;
}
int main(){
	ll x;
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++){
		scanf("%d",&N);
		for(int i=1;i<=N;i++) scanf("%lld",&num[i]);
		Gauss();
		scanf("%d",&Q);
		printf("Case #%d:\n",kase);
		while(Q--){
			scanf("%lld",&x);
			printf("%lld\n",query(x));
		}
	}
	return 0;
}
