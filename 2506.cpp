#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int up=1e8;
struct Num{
	int num[15];
	int top;
	Num(){memset(num,0,sizeof(num));top=0;}
};
Num dp[300];
void add(Num a,Num b,Num& c){
	int top=max(a.top,b.top);
	int jinwei=0;
	for(int i=0;i<=top;i++){
		int temp=a.num[i]+b.num[i]+jinwei;
		jinwei=temp/up;
		c.num[i]=temp%up;
	}
	if(jinwei>0){
		top++;
		c.num[top]=jinwei;
	}
	c.top=top;
}
void setval(Num& a,int x){
	if(x==0){
		memset(a.num,0,sizeof(a.num));
		a.top=0;
		return ;
	}
	int top=0;
	while(x){
		a.num[top++]=x%up;
		x/=up;
	}
	a.top=top-1;
}
void Print(Num a){
	printf("%d",a.num[a.top]);
	for(int i=a.top-1;i>=0;i--){
		printf("%08d",a.num[i]);
	}
	printf("\n");
}
void init(){
	memset(dp,0,sizeof(dp));
	setval(dp[0],1);
	setval(dp[1],1);
	setval(dp[2],3);
	for(int i=3;i<=280;i++){
		add(dp[i-2],dp[i-1],dp[i]);
		add(dp[i-2],dp[i],dp[i]);
	}
	//for(int i=0;i<=250;i++) Print(dp[i]);
}

int main(){
	int n;
	init();
	while(scanf("%d",&n)!=EOF){
		Print(dp[n]);
	}
	return 0;
}
