#include<stdio.h>
#include<algorithm>
using namespace std;

int n,k;
struct Jewel{
	int v,w;
	double rec;
	int id;
}jewel[100010];
bool cmp(const Jewel& a,const Jewel& b){
	return a.rec>b.rec;
}
bool C(double mid){
	for(int i=0;i<n;i++){
		jewel[i].rec=jewel[i].v-mid*jewel[i].w;
	}
	sort(jewel,jewel+n,cmp);
	double res=0;
	for(int i=0;i<k;i++){
		res+=jewel[i].rec;
	}
	if(res>=0){
		return true;
	}else{
		return false;
	}
}
bool cmp_id(const Jewel& a,const Jewel& b){
	return a.id<b.id;
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++){
		scanf("%d %d",&jewel[i].v,&jewel[i].w);
		jewel[i].id=i+1;
	}
	double ub=100000000;
	double lb=0;
	int cases=100;
	while(cases--){
		double mid=(ub+lb)/2;
		if(C(mid)){
			lb=mid;
		}else{
			ub=mid;
		}
	}
	sort(jewel,jewel+k,cmp_id);
	for(int i=0;i<k;i++){
		if(i!=0) printf(" ");
		printf("%d",jewel[i].id);
	}
	printf("\n");
	return 0;
}
