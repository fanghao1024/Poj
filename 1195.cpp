#include<stdio.h>
#include<string.h>

int ops,S;
int X,Y,A;
int L,B,R,T;
const int max_S=1030;
int t1[max_S][max_S],t2[max_S][max_S],t3[max_S][max_S],t4[max_S][max_S];
int lowbit(int x){
	return x&(-x);
}
void update(int x,int y,int d){
	for(int i=x;i<=S;i+=lowbit(i)){
		for(int j=y;j<=S;j+=lowbit(j)){
			t1[i][j]+=d;
			//t2[i][j]+=x*d;
			//t3[i][j]+=y*d;
			//t4[i][j]+=x*y*d;
		}
	}	
}
int sum(int x,int y){
	int res=0;
	for(int i=x;i;i-=lowbit(i)){
		for(int j=y;j;j-=lowbit(j)){
			//res+=(x+1)*(y+1)*t1[i][j]-(y+1)*t2[i][j]-(x+1)*t3[i][j]+t4[i][j];
			res+=t1[i][j];
		}
	}
	return res;
}
int sumAll(int x,int y,int x0,int y0){
	return sum(x0,y0)-sum(x0,y-1)-sum(x-1,y0)+sum(x-1,y-1);
}
int main(){
	
	while(scanf("%d",&ops) && ops!=3){
		switch (ops) {
		case 0:
			scanf("%d",&S);
			memset(t1,0,sizeof(t1));
			//memset(t2,0,sizeof(t2));
			//memset(t3,0,sizeof(t3));
			//memset(t4,0,sizeof(t4));
			break;
		case 1:
			scanf("%d %d %d",&X,&Y,&A);
			X++;
			Y++;
			update(X,Y,A);
			break;
		case 2:
			scanf("%d %d %d %d",&L,&B,&R,&T);
			L++;
			B++;
			R++;
			T++;
			printf("%d\n",sumAll(L,B,R,T));
			break;
		}
	}
	
	return 0;
}
