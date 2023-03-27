#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=32;

struct Matrix{
	int num[max_n<<1][max_n<<1];
};

int N,K,M,dim;
Matrix x;
Matrix operator*(const Matrix& a,const Matrix& b){
	Matrix c;
	memset(c.num,0,sizeof(c.num));
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			for(int k=0;k<dim;k++){
				c.num[i][j]=(c.num[i][j]+a.num[i][k]*b.num[k][j])%M;
			}
		}
	}
	return c;
}
Matrix MatMul(Matrix a,int n){
	Matrix c;
	memset(c.num,0,sizeof(c.num));
	for(int i=0;i<dim;i++) c.num[i][i]=1;
	while(n){
		if(n&1) c=c*a;
		a=a*a;
		n>>=1;
	}
	return c;
}
int main(){
	scanf("%d %d %d",&N,&K,&M);
	dim=2*N;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			scanf("%d",&x.num[i][j]);
		}
	}
	Matrix A;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			A.num[i][j]=A.num[i+N][j]=x.num[i][j];
		}
	}
	for(int i=0;i<N;i++){
		for(int j=N;j<2*N;j++){
			A.num[i][j]=A.num[i+N][j]=0;
			if(i==j-N){
				A.num[i+N][j]=1;
			}
		}
	}
	A=MatMul(A,K);
	for(int i=N;i<2*N;i++){
		for(int j=0;j<N;j++){
			if(j) printf(" ");
			printf("%d",A.num[i][j]);
		}
		printf("\n");
	}
	return 0;
}
