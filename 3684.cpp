#include<stdio.h>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

const double g=10.0;
double calc(double T,double H){
	if(T<0) return H;
	double t=sqrt(2*H/g);
	int k=int(T/t);
	if(k%2==0){
		return H-0.5*g*pow(T-k*t,2);
	}else{
		return H-0.5*g*pow(k*t+t-T,2);
	}
}
int main(){
	int C;
	int N,H,R,T;
	
	scanf("%d",&C);
	while(C--){
		scanf("%d %d %d %d",&N,&H,&R,&T);
		vector<double> vi;
		
		for(int i=0;i<N;i++){
			double hi=calc(T-i+0.0,H+2*R*i/100.0);
			//double hi=calc(T-i+0.0,H);
			vi.push_back(hi);
		}
		sort(vi.begin(),vi.end());
		for(int i=0;i<N;i++){
			if(i!=0) printf(" ");
			printf("%.2f",vi[i]+2*R*i/100.0);
		}
		printf("\n");
	}
	return 0;
}
