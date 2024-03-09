#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=5e5+10;

int N,rnk[max_n];
ll tree[max_n];
struct Node{
	int val;
	int id;
}node[max_n];
bool cmp(const Node& a,const Node& b){
	if(a.val==b.val) return a.id<b.id;
	return a.val<b.val;
}
int lowbit(int x){return x&-x;}
void update(int x,int d){
	while(x<=N){
		tree[x]+=d;
		x+=lowbit(x);
	}
}
int getsum(int x){
	ll res=0;
	while(x){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",&node[i].val),node[i].id=i;
	sort(node+1,node+1+N,cmp);
	for(int i=1;i<=N;i++) rnk[node[i].id]=i;
	ll ans=0;
	memset(tree,0,sizeof(tree));
	for(int i=N;i>0;i--){
		ans+=getsum(rnk[i]-1);
		update(rnk[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}
