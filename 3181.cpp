#include<stdio.h>

const int S=100000000;
const int M=8;
struct BigNum{
	int val[M];
	BigNum(){
		for(int i=0;i<M;i++){
			val[i]=0;
		}
	}
}bignum[1010];

void add(BigNum& b1,BigNum& b2){
	for(int i=0;i<M;i++){
		b1.val[i]+=b2.val[i];
	}
	for(int i=1;i<M;i++){
		b1.val[i]+=b1.val[i-1]/S;
	}
	for(int i=0;i<M;i++){
		b1.val[i]%=S;
	}
}

int main(){
	int N,K;
	scanf("%d %d",&N,&K);
	
	bignum[0].val[0]=1;

	for(int i=1;i<=K;i++){
		for(int j=1;j<=N;j++){
			if(j-i>=0){
				add(bignum[j],bignum[j-i]);
			}

		}
	}
	bool startzero=true;
	for(int i=M-1;i>=1;i--){
		if(bignum[N].val[i]==0&&startzero){
			continue;
		}
		startzero=false;
			
		printf("%d",bignum[N].val[i]);

		
	}
	printf("%d\n",bignum[N].val[0]);
	return 0;
}
