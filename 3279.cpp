#include<stdio.h>
#include<string.h>

int M,N;
int tile[20][20];
int flip[20][20];
int opt[20][20];
int dirx[5]={0,0,1,0,-1};
int diry[5]={0,-1,0,1,0};
int get_tile(int y,int x){
	int flag=tile[y][x];
	for(int i=0;i<5;i++){
		int dx=x+dirx[i];
		int dy=y+diry[i];
		if(dx>=0&&dx<N&&dy>=0&&dy<M){
			flag+=flip[dy][dx];
		}
	}
	return flag%2;
}
int calc(){
	int flag;
	int ops=0;
	for(int i=1;i<M;i++){
		for(int j=0;j<N;j++){
			flag=get_tile(i-1,j);
			if(flag==1) flip[i][j]=1;
		}	
	}
	for(int i=0;i<N;i++){
		if(get_tile(M-1,i)==1) return -1;
	}
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			if(flip[i][j]==1) ops++;
		}
	}
	return ops;
}
int main(){
	scanf("%d %d",&M,&N);
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			scanf("%d",&tile[i][j]);
		}
	}
	int min_ops=-1;
	for(int i=0;i<(1<<N);i++){
		memset(flip,0,sizeof(flip));
		for(int j=0;j<N;j++){
			flip[0][N-j-1]=(i>>j)&1;
		}
		int res=calc();
		
		if((res>0)&&(res<min_ops||min_ops<0)){
			min_ops=res;
			memcpy(opt,flip,sizeof(flip));
		}
	}
	if(min_ops<0){
		printf("IMPOSSIBLE\n");
	}else{
		for(int i=0;i<M;i++){
			for(int j=0;j<N;j++){
				if(j!=0) printf(" ");
				printf("%d",opt[i][j]);
			}
			printf("\n");
		}
	}
	
	return 0;
}
