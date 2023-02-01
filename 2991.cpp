#include <stdio.h>
#include<cmath>
const int max_n=10010;
const double Pi=acos(-1.0);
int lens[max_n];
int N,C;
double preAng[max_n];
double x[4*max_n];
double y[4*max_n];
double ang[4*max_n];
int S[1000000];
double A[1000000];

void init(int s,int l,int r){
	x[s]=0.0;
	ang[s]=0.0;
	
	if(r==l+1){
		y[s]=lens[l];
	}else{
		int sl=2*s+1;
		int sr=2*s+2;
		int mid=(l+r)>>1;
		init(sl,l,mid);
		init(sr,mid,r);
		y[s]=y[sl]+y[sr];
	}
	
}

void change(int s,double delta_a,int index,int l,int r){
	if(s<=l) return;
	if(s<r){
		int mid=(l+r)>>1;
		int sl=2*index+1;
		int sr=2*index+2;
		change(s,delta_a,sl,l,mid);
		change(s,delta_a,sr,mid,r);
		if(s<=mid) ang[index]+=delta_a;
		
		double sinx=sin(ang[index]);
		double cosx=cos(ang[index]);
		x[index]=x[sl]+(cosx*x[sr]-sinx*y[sr]);
		y[index]=y[sl]+(sinx*x[sr]+cosx*y[sr]);
	}
}
int main() {
	int case_num=0;
	while(scanf("%d %d",&N,&C)!=EOF){
		for(int i=0;i<N;i++) scanf("%d",&lens[i]);
		for(int i=0;i<C;i++){
			scanf("%d %lf",&S[i],&A[i]);
		}
		
		for(int i=1;i<N;i++) preAng[i]=Pi;
		init(0,0,N);

		if(case_num>0) printf("\n");
		
		for(int i=0;i<C;i++){
			int s=S[i];
			double a=A[i]/180.0*Pi;
			change(s,a-preAng[s],0,0,N);
			preAng[s]=a;
			printf("%.2f %.2f\n",x[0],y[0]);
		}
		case_num++;
	}
	return 0;
}