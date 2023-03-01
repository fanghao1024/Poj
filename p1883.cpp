#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=1e4+10;

int a[max_n],b[max_n],c[max_n];
int N;
double calc1(double x,int i){
	return a[i]*x*x+b[i]*x+c[i];
}
double calc(double mid){
	double res=calc1(mid,1);
	for(int i=2;i<=N;i++){
		res=max(res,calc1(mid,i));
	}
	return res;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=1;i<=N;i++){
			scanf("%d %d %d",&a[i],&b[i],&c[i]);
		}
		double ans;
		double l=0,r=1000;
		while(fabs(r-l)>1e-9){
			double d=(r-l)/3;
			double mid1=l+d,mid2=r-d;
			if(calc(mid1)>calc(mid2)){
				l=mid1;
			}else{
				r=mid2;
			}
		}
		printf("%.4f\n",calc(l));
	}
	return 0;
}

