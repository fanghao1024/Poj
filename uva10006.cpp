#include<stdio.h>

typedef long long ll;
ll mode_pow(ll x,ll n,ll mod){
	ll res=1;
	while(n>0){
		if(n&1){
			res=res*x%mod;
		}
		x=x*x%mod;
		n>>=1;
	}
	return res;
}
bool is_prime(ll x){
	for(ll i=2;i*i<=x;i++){
		if(x%i==0){
			return true;
		}
	}
	return false;
}
int main(){
	int num;
	while(1){
		scanf("%d",&num);
		if(num==0){
			break;
		}
		if(!is_prime(num)){
			printf("%d is normal.\n",num);
		}else{
			bool flag=true;
			for(ll i=2;i<num;i++){
				if(mode_pow(i,num,num)!=i){
					flag=false;
					printf("%d is normal.\n",num);
					break;
				}
			}
			if(flag){
				printf("The number %d is a Carmichael number.\n",num);
			}
		}
	}
	return 0;
}
