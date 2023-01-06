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
}bignum[105][1010];

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
	
	for(int i=0;i<=K;i++){
		bignum[i][0].val[0]=1;
	}
	for(int i=1;i<=N;i++){
		bignum[0][i].val[0]=0;
	}
	for(int i=1;i<=K;i++){
		for(int j=1;j<=N;j++){
			add(bignum[i][j],bignum[i-1][j]);
			if(j-i>=0){
				add(bignum[i][j],bignum[i][j-i]);
			}

		}
	}
	bool startzero=true;
	for(int i=M-1;i>=1;i--){
		if(bignum[K][N].val[i]==0&&startzero){
			continue;
		}
		startzero=false;
			
		printf("%d",bignum[K][N].val[i]);

		
	}
	printf("%d\n",bignum[K][N].val[0]);
	return 0;
}
