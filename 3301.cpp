#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;

const double Pi=acos(-1.0);
const int max_n=35;
const int inf=0x3f3f3f3f;
struct Point{
	double x,y;
}p[max_n];
int T,N;

double cal(double m){
	double Maxx=-inf,Maxy=-inf,Minx=inf,Miny=inf;
	for(int i=1;i<=N;i++){
		double x=p[i].x*cos(m)-p[i].y*sin(m);
		double y=p[i].x*sin(m)+p[i].y*cos(m);
		Maxx=max(Maxx,x);
		Maxy=max(Maxy,y);
		Minx=min(Minx,x);
		Miny=min(Miny,y);
	}
	return max(Maxx-Minx,Maxy-Miny);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=1;i<=N;i++){
			scanf("%lf %lf",&p[i].x,&p[i].y);
		}
		double l=0,r=Pi/2;
		while(r-l>1e-9){
			double d=(r-l)/3;
			double m1=l+d,m2=r-d;
			if(cal(m1)>cal(m2)){
				l=m1;
			}else{
				r=m2;
			}
		}
		double res=cal(l);
		printf("%.2f\n",res*res);
	}
	return 0;
}
