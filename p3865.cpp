#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=1e5+10;

int num[max_n],N,M;
int dp[max_n][20],Log2[max_n];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void init(){
	Log2[0]=-1;
	for(int i=1;i<=N;i++) Log2[i]=Log2[i>>1]+1;
	for(int i=1;i<=N;i++) dp[i][0]=num[i];
	for(int i=1;i<=Log2[N];i++){
		for(int j=1;j+(1<<i)-1<=N;j++){
			dp[j][i]=max(dp[j][i-1],dp[j+(1<<(i-1))][i-1]);
		}
	}
}
int query(int l,int r){
	int k=Log2[r-l+1];
	return max(dp[l][k],dp[r-(1<<k)+1][k]);
}
int main(){
	//scanf("%d %d",&N,&M);
	N=read();M=read();
	for(int i=1;i<=N;i++) num[i]=read();//scanf("%d",&num[i]);
	init();
	int l,r;
	while(M--){
		//scanf("%d %d",&l,&r);
		l=read();
		r=read();
		printf("%d\n",query(l,r));
	}
	return 0;
}

