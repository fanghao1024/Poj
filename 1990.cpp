#include <iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

typedef long long ll;
int N;
const int max_n=20010;
struct Cow{
	ll val;
	ll dis;
}cow[max_n];
ll tree[max_n];
ll distances[max_n];
bool cmp(const Cow& a,const Cow& b){
	if(a.val==b.val){
		return a.dis<b.dis;
	}else{
		return a.val<b.val;
	}
}
ll lowbit(ll x){
	return x&(-x);
}

void update(ll x,ll d,ll num[]){
	while(x<=max_n){
		num[x]+=d;
		x+=lowbit(x);
	}
}

ll get_sum(ll x,ll num[]){
	ll res=0;
	while(x>0){
		res+=num[x];
		x-=lowbit(x);
	}
	return res;
}

int main() {
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%lld %lld",&cow[i].val,&cow[i].dis);
	}
	sort(cow+1,cow+N+1,cmp);
	memset(tree,0,sizeof(tree));
	memset(distances,0,sizeof(distances));
	ll tsum=0;
	ll ans=0;
	for(int i=1;i<=N;i++){
		ll prenum=get_sum(cow[i].dis, tree);
		ll presum=get_sum(cow[i].dis, distances);
		//printf("%d:%d %d %d %d\n",i,cow[i].val,cow[i].dis,prenum,presum);
		//printf("pre ans: %d\n",ans);
		ans+=cow[i].val*(prenum*cow[i].dis-presum);
		//printf("^^^^^%d %d %d %d\n",cow[i].val,prenum,cow[i].dis,presum);
		//printf("~~%d\n",ans);
		ans+=cow[i].val*(tsum-presum-(i-prenum-1)*cow[i].dis);
		//printf("~~~~%d\n",ans);
		update(cow[i].dis,1,tree);
		update(cow[i].dis,cow[i].dis,distances);
		tsum+=cow[i].dis;
		//printf("===%d\n",tsum);
	}
	printf("%lld\n",ans);
	return 0;
}