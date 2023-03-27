#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int inf=0x3f3f3f3f;

int Hash[1024],cnt;
struct Matrix{
	int num[105][105];
};
Matrix g;
int N,T,S,E;
Matrix operator*(const Matrix& a,const Matrix& b){
	Matrix c;
	memset(c.num,inf,sizeof(c.num));
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++){
			for(int k=1;k<=cnt;k++){
				c.num[i][j]=min(c.num[i][j],a.num[i][k]+b.num[k][j]);
			}
		}
	}
	return c;
}
Matrix MatMul(Matrix a,int n){
	Matrix ans=a;
	n--;
	while(n){
		if(n&1) ans=ans*a;
		a=a*a;
		n>>=1;
	}
	return ans;
}
int main(){
	cnt=0;
	memset(Hash,0,sizeof(Hash));
	scanf("%d %d %d %d",&N,&T,&S,&E);
	
	int L,l1,l2;
	//Matrix g;
	memset(g.num,inf,sizeof(g.num));
	while(T--){
		scanf("%d %d %d",&L,&l1,&l2);
		if(!Hash[l1]) Hash[l1]=++cnt;
		if(!Hash[l2]) Hash[l2]=++cnt;
		g.num[Hash[l1]][Hash[l2]]=g.num[Hash[l2]][Hash[l1]]=L;
	}
	g=MatMul(g,N);
	printf("%d\n",g.num[Hash[S]][Hash[E]]);
	 
	return 0;
}
