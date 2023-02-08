#include<stdio.h>

long long is_prime(long long x){
	long long i=2;
	for(;i*i<x;i++){
		if(x%i==0){
			return i;
		}
	}
	return -1;
}

int main(){
	int T;
	long long num;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&num);
		long long result=is_prime(num);
		if(result==-1){
			printf("Prime\n");
		}else{
			printf("%lld\n",result);
		}
	}
	return 0;
}
