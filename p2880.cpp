#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=5e4+10;

int mast[max_n][20],mist[max_n][20];
int h[max_n];
int N,Q;
int Log2[max_n];

void init(){
	Log2[0]=-1;
	for(int i=1;i<=N;i++) Log2[i]=Log2[i>>1]+1;
	for(int i=1;i<=N;i++) mast[i][0]=mist[i][0]=h[i];
	for(int i=1;i<=Log2[N];i++){
		for(int j=1;j+(1<<i)-1<=N;j++){
			mist[j][i]=min(mist[j][i-1],mist[j+(1<<(i-1))][i-1]);
			mast[j][i]=max(mast[j][i-1],mast[j+(1<<(i-1))][i-1]);
		}
	}
}
int query(int l,int r,bool flag){
	int len=Log2[r-l+1];
	if(flag){
		return max(mast[l][len],mast[r-(1<<len)+1][len]);
	}
	else return min(mist[l][len],mist[r-(1<<len)+1][len]);
}
int main(){
	
	scanf("%d %d",&N,&Q);
	for(int i=1;i<=N;i++) scanf("%d",&h[i]);
	init();
	int l,r;
	while(Q--){
		scanf("%d %d",&l,&r);
		printf("%d\n",query(l,r,1)-query(l,r,0));
	}
	return 0;
}
