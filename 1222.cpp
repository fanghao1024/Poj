#include<stdio.h>
#include<string.h>

int rec[5][6];
int flip[5][6];
int dir_row[5]={0,-1,0,1,0};
int dir_col[5]={0,0,1,0,-1};
int temp(int row,int col){
	int res=0;
	int dr,dc;
	for(int i=0;i<5;i++){
		dr=row+dir_row[i];
		dc=col+dir_col[i];
		if(dr>=0&&dr<5&&dc>=0&&dc<6){
			res+=flip[dr][dc];
		}
	}
	res+=rec[row][col];
	return res%2;
}
bool calc(){
	for(int i=1;i<5;i++){
		for(int j=0;j<6;j++){
			int front_item=temp(i-1,j);
			flip[i][j]=front_item;
		}
	}
	for(int j=0;j<6;j++){
		if(temp(4,j)==1) return false;
	}
	return true;
}
int main(){
	int N;
	scanf("%d",&N);
	for(int case_num=1;case_num<=N;case_num++){
		for(int i=0;i<5;i++){
			for(int j=0;j<6;j++){
				scanf("%d",&rec[i][j]);
			}
				
		}
		for(int i=0;i<(1<<6);i++){
			memset(flip,0,sizeof(flip));
			for(int j=0;j<6;j++){
				flip[0][5-j]=(i>>j)&1;
			}
			if(calc()) break;
			
		}
		printf("PUZZLE #%d\n",case_num);
		for(int i=0;i<5;i++){
			for(int j=0;j<6;j++){
				if(j) printf(" ");
				printf("%d",flip[i][j]);
			}
			printf("\n");
		}
	}
	
	return 0;
}
