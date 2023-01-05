#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int matrix[400][400];
int result[400][400];
int main(){
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		for(int j=0;j<=i;j++){
			scanf("%d",&matrix[i][j]);
		}
	}
	memset(result,-1,sizeof(result));
	result[0][0]=matrix[0][0];
	for(int i=1;i<N;i++){
		for(int j=0;j<=i;j++){

			result[i][j]=max(result[i-1][j],result[i][j]);
			
			if(j-1>=0){
				result[i][j]=max(result[i-1][j-1],result[i][j]);
			}
			result[i][j]+=matrix[i][j];
			//printf("%d %d %d\n",i,j,result[i][j]);
		}
	}
	int min_num=-1;
	for(int i=0;i<N;i++){
		if(result[N-1][i]>min_num){
			min_num=result[N-1][i];
		}
	}
	printf("%d\n",min_num);
	return 0;
}
