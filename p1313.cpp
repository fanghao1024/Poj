#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int Mod=10007;
const int max_k=1024;
int C[max_k][max_k];

int a,b,k,n,m;
int fast_pow(int x,int s){
	int res=1;
	x%=Mod;
	while(s){
		if(s&1){
			res=(res*x)%Mod;
		}
		x=(x*x)%Mod;
		s>>=1;
	}
	return res;
}
int c(int N,int R){
	if(!R) return C[N][R]=1;
	if(R==1) return C[N][R]=N;
	if(C[N][R]) return C[N][R];
	if(N-R<R) R=N-R;
	C[N][R]=(c(N-1,R-1)+c(N-1,R))%Mod;
	return C[N][R];
}
int main(){
	scanf("%d %d %d %d %d",&a,&b,&k,&n,&m);
	C[1][0]=C[1][1]=1;
	int ans=((fast_pow(a,n)%Mod)*(fast_pow(b,m)%Mod))%Mod;
	printf("%d\n",(ans*(c(k,n)%Mod))%Mod);
	return 0;
}
