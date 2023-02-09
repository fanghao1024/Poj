#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int N;
const int max_n=305;
int rec[max_n][max_n];
int main() {
	scanf("%d",&N);
	
	for(int case_num=1;case_num<=N;case_num++){
		int M,K;
		scanf("%d %d",&M,&K);
		memset(rec,0,sizeof(rec));
		int x,y;
		for(int i=0;i<K;i++){
			scanf("%d %d",&x,&y);
			rec[x][y]=1;
		}
		bool flag1,flag2;
		bool flag=false;
		
			
		for(int i=0;i<M;i++){
			for(int j=0;j<M;j++){
				flag1=flag2=false;
				for(int k=0;k<M;k++){
					if(rec[i][k]&&rec[j][k]) flag1=true;
					if(rec[i][k]+rec[j][k]==1) flag2=true;
				}
				if(flag1&&flag2){
					flag=true;
					break;
				}
			}
			if(flag){
				break;
			}
		}
		if(flag){
			printf("Case #%d: No\n",case_num);
		}else{
			printf("Case #%d: Yes\n",case_num);
		}
		
	}
	return 0;
}