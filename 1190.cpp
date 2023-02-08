#include<cstdio>
#include<cmath>

const int max_m=25;
int N,M;
int S;
int recR[max_m];
int recH[max_m];
int recV[max_m];
int recS[max_m];
bool dfs(int R,int H,int m,int V,int minS){
	if(m==0){
		if(V==0){
			int v=0;
			for(int i=1;i<=M;i++){
				v+=2*recR[i]*recH[i];
			}
			v+=recR[1]*recR[1];
			if(v<S) S=v;
			return true;
		}else{
			return false;
		}
		
	}
	bool flag=false;
	for(int i=R-1;i>=m;i--){
		for(int j=H-1;j>=m;j--){
			recR[M-m+1]=i;
			recH[M-m+1]=j;
			int v=V-i*i*j;
			
			if(v>=recV[m-1]&&minS+2*i*j+recS[m-1]<S){
				if(dfs(i,j,m-1,v,minS+2*i*j)){
					flag=true;
				}
			}
			
		}
	}
	return flag;
}
int main(){
	
	recS[0]=0;
	recV[0]=0;
	for(int i=1;i<21;i++){
		recS[i]=recS[i-1]+2*i*i;
		recV[i]=recV[i-1]+i*i*i;
	}
	while(scanf("%d %d",&N,&M)!=EOF){
		S=0x3fffffff;
		bool flag=false;
		//for(int H=M;H<=N/M/M;H++){
		for(int H=N/M/M;H>=M;H--){
			//for(int R=M;R<=int(sqrt((N+0.0)/M));R++){
			for(int R=int(sqrt((N+0.0)/M));R>=M;R--){
				recH[1]=H;
				recR[1]=R;
				int s=2*R*H+R*R;
				if(N-R*R*H>=recV[M-1]&&s+recS[M-1]<S){
					if(dfs(R,H,M-1,N-R*R*H,s)){
						flag=true;
					}
				}
				
			}
		}
		if(flag){
			printf("%d\n",S);
		}else{
			printf("0\n");
		}
	}
	return 0;
}
