#include<stdio.h>
#include<algorithm>
using namespace std;

const int max_n=310;
int dis[max_n][max_n];
int rec[max_n];

int main(){
	int N,M;
	while(scanf("%d %d",&N,&M)!=EOF){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				dis[i][j]=max_n;
			}
		}
		int case_num;
		for(int i=0;i<M;i++){
			scanf("%d",&case_num);
			for(int j=0;j<case_num;j++){
				scanf("%d",&rec[j]);
			}
			for(int j=0;j<case_num;j++){
				for(int k=j;k<case_num;k++){
					if(k==j){
						dis[rec[k]-1][rec[j]-1]=0;
					}else{
						dis[rec[k]-1][rec[j]-1]=dis[rec[j]-1][rec[k]-1]=1;
					}
				}
			}	
		}
		for(int k=0;k<N;k++){
			for(int i=0;i<N;i++){
				for(int j=0;j<N;j++){
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
				}
			}
		}
		
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				printf("%d ",dis[i][j]);
			}
			printf("\n");
		}
		
		double res=max_n*N;
		
		for(int i=0;i<N;i++){
			double counts=0;
			double row_sum=0;
			for(int j=0;j<N;j++){
				if(i!=j&&dis[i][j]!=max_n){
					row_sum+=dis[i][j];
					counts+=1;
				}
				res=res<row_sum/counts?res:row_sum/counts;
			}
		}
		printf("%d\n",int(100*res));
	}
	return 0;
}
