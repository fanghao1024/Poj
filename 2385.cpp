#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

int num[1010];
int ans[1010][33][2];
int main(){
	int T,W;
	scanf("%d %d",&T,&W);
	for(int i=0;i<T;i++){
		scanf("%d",&num[i]);
	}
	memset(ans,-1,sizeof(ans));
	ans[0][0][0]=(num[0]==1);
	ans[0][1][1]=(num[0]==2);
	for(int i=1;i<T;i++){
		for(int j=0;j<=W;j++){
			for(int k=0;k<2;k++){
				if(ans[i-1][j][k]>=0){
					ans[i][j][k]=max(ans[i][j][k],ans[i-1][j][k]+(num[i]==k+1));
				}
				if(ans[i-1][j-1][1-k]>=0){
					ans[i][j][k]=max(ans[i][j][k],ans[i-1][j-1][1-k]+(num[i]==k+1));
				}
			}
			
		}
	}
	int result=-1;
	for(int i=0;i<=W;i++){
		result=max(max(result,ans[T-1][i][0]),ans[T-1][i][1]);
	}
	printf("%d\n",result);
	return 0;
}
