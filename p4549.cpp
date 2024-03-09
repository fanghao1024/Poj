#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int max_n=25;

int N;
int num[max_n];
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%d",&num[i]);
	}
	for(int i=2;i<=N;i++){
		num[i]=gcd(num[i],num[i-1]);
	}
	printf("%d\n",abs(num[N]));
	return 0;
}
