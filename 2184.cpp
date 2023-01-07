#include<stdio.h>
#include<cstring>

int record[2*100*1000+10];
int S[105];
int F[105];
const int inf=-1000000;
int main(){
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%d %d",&S[i],&F[i]);
	}
	
	for(int i=0;i<2*100*1000+10;i++){
		record[i]=inf;
	}
	record[100*1000]=0;
	for(int i=0;i<N;i++){
		if(S[i]>=0){
			for(int j=2*100*1000;j>=S[i];j--){
				if(record[j-S[i]]>inf){
					record[j]=record[j]>(record[j-S[i]]+F[i])?record[j]:(record[j-S[i]]+F[i]);
				}
			}
		}else{
			for(int j=0;j-S[i]<=2*100*1000;j++){
				if(record[j-S[i]]>inf){
					record[j]=record[j]>(record[j-S[i]]+F[i])?record[j]:(record[j-S[i]]+F[i]);
				}
				
			}
		}
	}
	int ans=inf;

	for(int j=100*1000;j<=2*100*1000;j++){
		if(record[j]>=0){
			ans=ans>(record[j]+j-100*1000)?ans:(record[j]+j-100*1000);
		}
		
	}
	ans=ans>=0?ans:0;
	printf("%d\n",ans);
	return 0;
}
