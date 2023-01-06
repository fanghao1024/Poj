#include<stdio.h>
#include<string.h>

int record[1010][100010];
int family[1010];
#define M 1000000
int main(){
	int T,A,S,B;
	scanf("%d %d %d %d",&T,&A,&S,&B);
	memset(family,0,sizeof(family));
	int signs;
	for(int i=0;i<A;i++){
		scanf("%d",&signs);
		family[signs]++;
	}
	int i,j;
	for(i=0;i<=T;i++){
		record[i][0]=1;
	}
	for(i=1;i<=B;i++){
		record[0][i]=0;
	}
	for(i=1;i<=T;i++){
		for(j=1;j<=B;j++){
			if(j-1-family[i]<0){
				record[i][j]=(record[i][j-1]+record[i-1][j]+M)%M;
			}else{
				record[i][j]=(record[i][j-1]+record[i-1][j]-record[i-1][j-1-family[i]]+M)%M;
			}
		}
	}
	int ans=0;
	for(i=S;i<=B;i++){
		ans=(ans+record[T][i]+M)%M;
	}
	printf("%d\n",ans);
	return 0;
}
