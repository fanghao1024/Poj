#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
const int max_w=1e5+10;

int N,W;
int v,w,m;
int dp[max_w],q[max_w],num[max_w];

int main(){
	scanf("%d %d",&N,&W);
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=N;i++){
		scanf("%d %d %d",&v,&w,&m);
		if(m>W/w) m=W/w;
		for(int b=0;b<w;b++){
			int head=1,tail=0;
			for(int y=0;y<=(W-b)/w;y++){
				int temp=dp[b+y*w]-y*v;
				while(head<=tail&&q[tail]<=temp) tail--;
				q[++tail]=temp;
				num[tail]=y;
				while(head<=tail&&y-num[head]>m) head++;
				dp[b+y*w]=max(dp[b+y*w],q[head]+y*v);
			}
		}
	}	
	printf("%d\n",dp[W]);
	return 0;
}

