#include<stdio.h>
#include<cmath>
int N;
double A;
double ans;
bool check(double mid){
	double pre=A;
	double cur=mid;
	double next1;
	for(int i=3;i<=N;i++){
		next1=2*cur+2-pre;
		if(next1<0) return false;
		pre=cur;
		cur=next1;
	}
	ans=mid;
	return true;
}
int main(){
	
	scanf("%d %lf",&N,&A);
	double lb=0;
	double ub=1000000;
	
	for(int i=0;i<100;i++){
		double mid=(lb+ub)/2;
		if(check(mid)){
			ub=mid;
		}else{
			lb=mid;
		}
	}
	double pre=A;
	double cur=ans;
	double next1;
	for(int i=3;i<=	N;i++){
		next1=2*cur+2-pre;
		pre=cur;
		cur=next1;
	}
	printf("%.2f\n",cur);
	return 0;
}
