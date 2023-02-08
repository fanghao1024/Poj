#include<stdio.h>
#include<cmath>
typedef long long ll;
int main(){
	ll a,b;
	while(scanf("%lld %lld",&a,&b)!=EOF){
		ll c=b/a;
		
		ll i=ll(sqrt(c+0.0));
		for(;i>1;i--){
			if(c%i==0){
				break;
			}
		}
		printf("%lld %lld\n",i*a,(c/i)*a);
	}
	return 0;
}
