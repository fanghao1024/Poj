#include<stdio.h>
#include<algorithm>
using namespace std;

int n,k;
const int max_n=1010;
struct Info{
	int a,b;
	double rec;
}info[max_n];
bool cmp(const Info& a,const Info& b){
	return a.rec>b.rec;
}
bool C(double mid){
	for(int i=0;i<n;i++){
		info[i].rec=info[i].a-mid*info[i].b;
	}
	sort(info,info+n,cmp);
	double res=0;
	for(int i=0;i<n-k;i++){
		res+=info[i].rec;
	}
	if(res>=0) return true;
	return false;
}
int main(){
	while(scanf("%d %d",&n,&k)){
		if(n==0&&k==0) break;
		for(int i=0;i<n;i++){
			scanf("%d",&info[i].a);
		}
		for(int i=0;i<n;i++){
			scanf("%d",&info[i].b);
		}
		double lb=0;
		double ub=1.0;
		while(ub-lb>0.0001){
			double mid=(lb+ub)/2;
			//printf("%lf %lf %lf\n",)
			if(C(mid)){
				lb=mid;
			}else{
				ub=mid;
			}
		}
		printf("%d\n",int(lb*100+0.5));
	}
	
	return 0;
}
