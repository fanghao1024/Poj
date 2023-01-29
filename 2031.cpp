#include<stdio.h>
#include<string.h>
#include<cmath>

const int max_n=103;
double dis[max_n][max_n];
double rec[max_n];
double x[max_n],y[max_n],z[max_n],r[max_n];
bool vis[max_n];
int par[max_n];
int N;
double calc_dis(int a,int b){
	return sqrt(pow(x[a]-x[b],2)+pow(y[a]-y[b],2)+pow(z[a]-z[b],2))-r[a]-r[b];
}
double prim(int u){
	for(int i=1;i<=N;i++) rec[i]=0x3fffffff;
	memset(vis,0,sizeof(vis));
	rec[u]=0;
	vis[u]=1;
	par[u]=u;
	double ans=0;
	for(int i=1;i<N;i++){
		double d=0x3fffffff;
		int t=1;
		for(int j=1;j<=N;j++){
			if(!vis[j]){
				if(rec[j]>dis[u][j]){
					rec[j]=dis[u][j];
					par[j]=u;
				}
				if(rec[j]<d){
					d=rec[j];
					t=j;
				}
			}
		}
		if(t==1){
			return -1.0;
		}
		vis[t]=1;
		ans+=rec[t];
		//printf("~~~%d %lf\n",t,dis[t][par[t]]);
		u=t;
		
	}
	return ans;
}
int main(){
	while(scanf("%d",&N)&&N){
		for(int i=1;i<=N;i++){
			scanf("%lf%lf%lf%lf",x+i,y+i,z+i,r+i);
		}
		for(int i=1;i<=N;i++){
			for(int j=i;j<=N;j++){
				if(i==j){
					dis[i][j]=0.00;
				}else{
					double d=calc_dis(i,j);
					if(d<0){
						dis[i][j]=dis[j][i]=0.000;
					}else{
						dis[i][j]=dis[j][i]=d;
					}
				}
			}
		}
		

		double ans=prim(1);
		printf("%.3f\n",ans);
	}
	return 0;
}
