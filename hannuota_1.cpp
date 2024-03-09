#include<cstdio>

int n,m,sum;
void hani(char a,char b,char c,int k){
	if(k==1){
		sum++;
		if(sum==m) printf("#%d:%c->%c\n",k,a,c);
	}else{
		hani(a,c,b,k-1);
		sum++;
		if(sum==m) printf("#%d:%c->%c\n",k,a,c);
		hani(b,a,c,k-1);
	}
}
int main(){
	scanf("%d %d",&n,&m);
	sum=0;
	hani('A','B','C',n);
	printf("%d\n",sum);
	return 0;
}
