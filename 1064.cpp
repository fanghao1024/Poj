#include<stdio.h>
#include<cmath>
int N,K;
double num[10010];
bool judge(double x){
	int k=0;
	for(int i=0;i<N;i++){
		k+=int(num[i]/x);
	}
	return k>=K;
}
int main(){
	
	scanf("%d %d",&N,&K);
	for(int i=0;i<N;i++){
		scanf("%lf",&num[i]);
	}
	double lb=0;
	double ub=100001;
	double value;
	while(ub-lb>0.0001){
		value=(ub+lb)/2;
		if(judge(value)){
			lb=value;
		}else{
			ub=value;
		}
	}
	printf("%.2f\n",int(ub*100)/100.0);
	return 0;
}
