#include<stdio.h>

int N,M;
const int max_n=2060;
int t1[max_n][max_n],t2[max_n][max_n],t3[max_n][max_n],t4[max_n][max_n];
#define lowbit(x) x&(-x)

void update(int x,int y,int delta){
	for(int i=x;i<=N;i+=lowbit(i)){
		for(int j=y;j<=M;j+=lowbit(j)){
			t1[i][j]+=delta;
			t2[i][j]+=delta*x;
			t3[i][j]+=delta*y;
			t4[i][j]+=delta*x*y;
		}
	}
}
int sum(int x,int y){
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i)){
		for(int j=y;j>0;j-=lowbit(j)){
			ans+=(x+1)*(y+1)*t1[i][j]-(y+1)*t2[i][j]-(x+1)*t3[i][j]+t4[i][j];
		}
	}
	return ans;
}

int main(){
	char X;
	scanf(" %c %d %d",&X,&N,&M);
	int a,b,c,d,delta;
	while(scanf(" %c",&X)!=EOF){
		scanf("%d %d %d %d",&a,&b,&c,&d);
		switch (X) {
		case 'L':
			scanf("%d",&delta);
			update(a,b,delta);
			update(c+1,d+1,delta);
			update(a,d+1,-delta);
			update(c+1,b,-delta);
			break;
		case 'k':
			printf("%d\n",sum(c,d)+sum(a-1,b-1)-sum(a-1,d)-sum(c,b-1));
			break;

		}
	}
	return 0;
}
