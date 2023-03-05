#include<cstdio>
#include<cmath>

const int MOD=9901;
int a,b;

int main(){
	scanf("%d %d",&a,&b);
	int res=1;
	int x=1;
	for(int i=1;i<=b;i++){
		x=(x*a)%MOD;
		res=(res+x)%MOD;
	}
	printf("%d\n",res);
	return 0;
}

