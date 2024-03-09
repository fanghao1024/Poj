#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int T,N;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
	scanf("%d",&T);
	int a,b;
	for(int kase=1;kase<=T;kase++){
		scanf("%d %d %d",&N,&a,&b);
		int m=N/gcd(a,b);
		printf("Case #%d: %s\n",kase,(m&1)?"Yuwgna":"Iaka");
	}
	return 0;
}
