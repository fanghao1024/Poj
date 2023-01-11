#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int INF=0x3f3f3f3f;
int N;
double A,ans;
double judge(double d){
	int i;
	double tmp,tmp1,tmp2;
	tmp1=A,tmp2=d;
	for(i=3;i<=N;i++){                  //二分第二个点的位置，因此通过第一个点和第二个点
		tmp=tmp2;                       //可以推出所有的点的位置
		tmp2=2*tmp2+2-tmp1;
		tmp1=tmp;
		if(tmp2<0)                      //看是否在第一象限
			return 0;
	}
	ans=tmp2;                           //记录答案
	return 1;
}
int main(){
	int i,j;
	double l,r,mid;
	while(scanf("%d%lf",&N,&A)!=EOF){
		l=0,r=1.0*INF;
		for(i=0;i<100;i++){
			mid=(l+r)/2;
			if(judge(mid))
				r=mid;
			else
				l=mid;
		}
		printf("%.2lf\n",ans);
	}
	return 0;
}
