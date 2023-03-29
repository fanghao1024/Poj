#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_n=105;
const double eps=1e-7;
double a[max_n][max_n];
int N;
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N+1;j++)
			scanf("%lf",&a[i][j]);
	}
	
	int Max;
	for(int i=1;i<=N;i++){ //第i列
		Max=i;
		for(int j=i+1;j<=N;j++){ //第j行
			if(a[j][i]>a[Max][i]) Max=j;
		}
		for(int j=1;j<=N+1;j++) swap(a[i][j],a[Max][j]);
		if(fabs(a[i][i])<eps){
			printf("No Solution\n");
			return 0;
		}
		for(int j=N+1;j>=1;j--) a[i][j]/=a[i][i];
		for(int j=1;j<=N;j++){
			if(j!=i){
				double temp=a[j][i]/a[i][i];
				for(int k=1;k<=N+1;k++){
					a[j][k]-=temp*a[i][k];
				}
			}
		}
	}
	for(int i=1;i<=N;i++) printf("%.2f\n",a[i][N+1]);
	return 0;
}
