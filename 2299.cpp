#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;

typedef long long ll;
const int max_n=500010;
struct Point{
	ll value;
	int id;
}point[max_n];
ll rec[max_n];
ll tree[max_n];
int N;
bool cmp(const Point& a,const Point& b){
	if(a.value==b.value) return a.id<b.id;
	return a.value<b.value;
}

#define lowbit(x) x&(-x)
void update(int x,ll d){
	while(x<=N){
		tree[x]+=d;
		x+=lowbit(x);
	}
}
int sum(int x){
	ll res=0;
	while(x>0){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	while(scanf("%d",&N)){
		if(!N) break;
		for(int i=1;i<=N;i++){
			scanf("%lld",&point[i].value);
			point[i].id=i;
		}
		sort(point+1,point+N+1,cmp);
		for(int i=1;i<=N;i++){
			rec[point[i].id]=i;
		}
		memset(tree,0,sizeof(tree));
		long long ans=0;
		for(int i=N;i>0;i--){
			update(rec[i],1);
			ans+=sum(rec[i]-1);
		}
		printf("%lld\n",ans);
	
	}
	return 0;
}
