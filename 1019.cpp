#include<stdio.h>
#include<cmath>
typedef long long ll;
const ll max_n=40000;
ll a[max_n],sum[max_n];
int main(){
	int T;
	long long I;
	a[0]=0;
	sum[0]=0;
	for(int i=1;i<max_n;i++){
		a[i]=a[i-1]+int(log10(i+0.0))+1;
		sum[i]=sum[i-1]+a[i];
	}
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&I);
		int t=0;
		while(sum[t]<I){
			t++;
		}
		int pos=I-sum[t-1];
		int len=0,k=0;
		while(len<pos){
			k++;
			len+=int(log10(k+0.0))+1;
		}
		printf("%d\n",int(k/(pow(10.0,len-pos)))%10);
	}
	return 0;
}
