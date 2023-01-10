#include<stdio.h>

typedef long long ll;
const int max_n=4505;
ll A[max_n];
ll B[max_n];
ll moda(ll a,ll b,ll n){
	ll res=1;
	while(b>0){
		if((b&1)==1) res=res*a%n;
		a=a*a%n;
		b>>=1;
	}
	return res;
}
int main(){
	ll Z,M,H;
	scanf("%lld\n",&Z);
	while(Z--){
		scanf("%lld",&M);
		scanf("%lld",&H);
		for(int i=0;i<H;i++){
			scanf("%lld %lld",&A[i],&B[i]);
		}
		ll res=0;
		for(int i=0;i<H;i++){
			res=(res+moda(A[i],B[i],M))%M;
		}
		printf("%lld\n",res);
	}
	return 0;
}
