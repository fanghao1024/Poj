#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int mains(){
	int a,b;
	while(scanf("%d%d",&a,&b)!=EOF){
		if(gcd(a,b)==1) printf("%10d%10d     %s\n\n",a,b,"Good Choice");
		else printf("%10d%10d    %s\n\n",a,b,"Bad Choice");
	}
	return 0;
}
int main() {
	int n,m;
	while(scanf("%d%d",&n,&m)>0){
		printf("%10d%10d    %sd Choice\n\n", n,m,(gcd(n,m)^1)?"Ba":"Goo");
	}
	return 0;
}
