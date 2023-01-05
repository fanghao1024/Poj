#include<stdio.h>
#include<string.h>

int ans[1000010];
int value[25];
int main(){
	int N;
	scanf("%d",&N);
	value[1]=1;
	int index=1;
	for(int i=2;value[i-1]<N;i++){
		value[i]=2*value[i-1];
		index++;
	}
	for(int i=1;i<=index;i++){
		for(int j=0;j<=N;j++){
			if(i==1){
				ans[j]=1;
			}else{
				if(j-value[i]>=0){
					ans[j]+=ans[j-value[i]];
					ans[j]=ans[j]%1000000000;
				}
			}
		}
	}
	printf("%d\n",ans[N]);
	
	return 0;
}
