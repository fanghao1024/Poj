#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=18;
const int inf=0x3f3f3f3f;

double dp[1<<max_n][max_n];
double dis[max_n][max_n];
struct Point{
	double x,y;
}p[max_n];
int N;
double calDis(int i,int j){
	return sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y));
}
double distance(int v,int w)//计算第v个和第w个奶酪之间的距离 
{
	return sqrt((p[v].x-p[w].x)*(p[v].x-p[w].x)+(p[v].y-p[w].y)*(p[v].y-p[w].y));//两点间距离公式 
}
int main(){
	memset(dp,127,sizeof(dp));
	double ans=dp[0][0];
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
	p[0].x=0;
	p[0].y=0;
	//dp[0][0]=0;
	for(int i=0;i<=N;i++){
		for(int j=i+1;j<=N;j++){
			dis[i][j]=dis[j][i]=distance(i,j);
		}
	}
	for(int i=1;i<=N;i++) dp[1<<(i-1)][i]=dis[0][i];
	for(int S=1;S<(1<<N);S++){
		for(int i=1;i<=N;i++){
			if((S&(1<<(i-1)))==0) continue;
			for(int j=1;j<=N;j++){
				if(i==j) continue;
				if((S&(1<<(j-1)))==0) continue;
				dp[S][i]=min(dp[S][i],dp[S-(1<<(i-1))][j]+dis[j][i]);
			}
		}
	}
	
	for(int i=1;i<=N;i++) ans=min(ans,dp[(1<<N)-1][i]);
	printf("%.2f\n",ans);
	return 0;
}
