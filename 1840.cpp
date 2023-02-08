#include<stdio.h>
#include<string.h>
#include<cmath>

const int max_n=25000010;
const int add=12500000;
short rec[max_n];
int cal(int x){
	return x*x*x;
}
int main(){
	memset(rec,0,sizeof(rec));
	int a1,a2,a3,a4,a5;
	scanf("%d%d%d%d%d",&a1,&a2,&a3,&a4,&a5);
	int x1,x2,x3,x4,x5;
	for(x1=-50;x1<=50;x1++){
		for(x2=-50;x2<=50;x2++){
			if(x1==0||x2==0) continue;
			rec[a1*cal(x1)+a2*cal(x2)+add]++;
		}
	}
	int ans=0;
	for(x3=-50;x3<=50;x3++){
		for(x4=-50;x4<=50;x4++){
			for(x5=-50;x5<=50;x5++){
				if(x3==0||x4==0||x5==0) continue;
				int temp=add-(a3*cal(x3)+a4*cal(x4)+a5*cal(x5));
				if(temp>=0&&temp<max_n)
					ans+=rec[temp];
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
