#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef int ll;
const int K=2;
const int Mod=10000;

ll N;
struct Matrix{
	ll num[K][K];
};

Matrix operator*(const Matrix& a,const Matrix& b){
//Matrix mul(const Matrix& a,const Matrix& b){
	Matrix c;
	//memset(c.num,0,sizeof(c.num));
	for(int i=0;i<K;i++){
		for(int j=0;j<K;j++){
			c.num[i][j]=0;
			for(int k=0;k<K;k++){
				c.num[i][j]=(c.num[i][j]+a.num[i][k]*b.num[k][j]);
			}
			c.num[i][j]%=Mod;
		}
	}
	return c;
}
Matrix MatMul(Matrix a,int n){
	Matrix c;
	memset(c.num,0,sizeof(c.num));
	for(int i=0;i<K;i++) c.num[i][i]=1;
	//c={1,0,0,1};
	while(n){
		if(n&1) //c=mul(c,a);
			c=c*a;
		//a=mul(a,a);
		a=a*a;
		n>>=1;
	}
	return c;
}
int main(){
	Matrix ans={1,1,1,0};
	while(scanf("%d",&N)!=EOF){
		if(N==-1) break;
		if(N==0){
			printf("0\n");
			continue;
		}
		
		//ans.num[0][0]=ans.num[0][1]=ans.num[1][0]=1;
		//ans.num[1][1]=0;
		Matrix res=MatMul(ans,N);
		printf("%d\n",res.num[0][1]);
	}
	return 0;
}
