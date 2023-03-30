#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


const int max_n=260;
const int max_w=1024;
const int inf=0x3f3f3f3f;
const double eps=1e-8;
int N,W;
struct Cow{
	int w,t;
	double y;
}cow[max_n];
double dp[max_w];
bool check(double mid){
	for(int i=1;i<=N;i++) cow[i].y=cow[i].t-mid*cow[i].w;
	for(int i=1;i<=W;i++) dp[i]=-inf;
	dp[0]=0;
	for(int i=1;i<=N;i++){
		for(int j=W;j>=0;j--){
			if(cow[i].w+j>=W) dp[W]=max(dp[W],dp[j]+cow[i].y);
			else dp[cow[i].w+j]=max(dp[cow[i].w+j],dp[j]+cow[i].y);
		}
	}
	return dp[W]>=0;
}
int main(){
	scanf("%d %d",&N,&W);
	for(int i=1;i<=N;i++) scanf("%d %d",&cow[i].w,&cow[i].t);
	double L=0,R=0;
	for(int i=1;i<=N;i++) R+=cow[i].t;
	int cnt=50;
	while(R-L>eps){
		double mid=(L+R)/2;
		if(check(mid)){
			L=mid;
		}else{
			R=mid;
		}
	}
	printf("%d\n",(int)(L*1000));
	return 0;
}
