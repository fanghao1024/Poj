#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxK=105;
const int maxN=16010;

int N,K;
struct Point{
	int l,p,s;
}P[maxK];
bool cmp(const Point& a,const Point& b){
	return a.s<b.s;
}
int dp[maxK][maxN];
int q[maxN];
int cal(int i,int k){
	return dp[i-1][k]-k*P[i].p;
}
int main(){
	scanf("%d %d",&N,&K);
	for(int i=1;i<=K;i++){
		scanf("%d %d %d",&P[i].l,&P[i].p,&P[i].s);
	}
	sort(P+1,P+1+K,cmp);
	for(int i=1;i<=K;i++){
		int head=1,tail=0;
		for(int k=max(0,P[i].s-P[i].l);k<P[i].s;k++){
			while(head<=tail&&cal(i,k)>=cal(i,q[tail])) tail--;
			q[++tail]=k;
		}
		/*
		for(int j=P[i].s;j<=P[i].s+P[i].l-1;j++){
			dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			while(head<=tail&&j-q[head]+1>P[i].l) head++;
			if(head<=tail) dp[i][j]=max(dp[i][j],cal(i-1,q[head]));
		}
		 */
		for(int j=1;j<=N;j++){
			dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			if(j>=P[i].s && j<P[i].s+P[i].l)
			{
				while(head<=tail && j-P[i].l>q[head]) head++;
				if(head<=tail) dp[i][j]=max(dp[i][j],P[i].p*j+cal(i,q[head]));
			}
		}
	}
	printf("%d\n",dp[K][N]);
	return 0;
}

