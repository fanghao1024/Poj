#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

int N,M;
int num[200010];
int tree[200010];
#define lowbit(x) (x&(-x))
void update(int x,int d){
	while(x<=N){
		tree[x]=d;
		for(int i=1;i<lowbit(x);i<<=1){
			tree[x]=max(tree[x],tree[x-i]);
		}
		x+=lowbit(x);
	}
}
int query(int L,int R){
	int ans=0;
	while(L<=R){
		ans=max(ans,num[R]);
		R--;
		while(R-lowbit(R)>=L){
			ans=max(ans,tree[R]);
			R-=lowbit(R);
		}
	}
	return ans;
}
int main(){
	char ch;
	int x,y;
	while(scanf("%d %d",&N,&M)!=EOF){
		for(int i=1;i<=N;i++) scanf("%d",&num[i]);
		memset(tree,0,sizeof(tree));
		for(int i=1;i<=N;i++) update(i,num[i]);
		while(M--){
			scanf(" %c %d %d",&ch,&x,&y);
			switch (ch) {
			case 'Q':
				printf("%d\n",query(x,y));
				break;
			case 'U':
				num[x]=y;
				update(x,y);
				break;
			}
		}
	}
	return 0;
}
