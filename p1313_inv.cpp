#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1024;
const int Mod=10007;
int a,b,k,n,m;
int f[max_n],inv[max_n];
int fast_pow(int a,int n){
	int res=1;
	a%=Mod;
	while(n){
		if(n&1) res=(res*a)%Mod;
		a=(a*a)%Mod;
		n>>=1;
	}
	return res;
}
int C(int k,int n){
	return (f[k]*inv[n]%Mod*inv[k-n]%Mod)%Mod;
}
int main(){
	scanf("%d %d %d %d %d",&a,&b,&k,&n,&m);
	f[0]=1;
	for(int i=1;i<=k;i++) f[i]=(f[i-1]*i)%Mod,inv[i]=fast_pow(f[i],Mod-2);
	printf("%d\n",(fast_pow(a,n)%Mod*fast_pow(b,m)%Mod*C(k,n))%Mod);
	return 0;
}
