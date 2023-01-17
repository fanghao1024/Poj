#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;

typedef long long ll;
const int max_n=20010;
struct Cow{
	ll vol,loc;
	int id;
}cow[max_n];
ll dis[max_n];
ll D[max_n];
int N;
#define lowbit(x) x&(-x)
void update(int x,ll value){
	while(x<=N){
		D[x]+=value;
		x+=lowbit(x);
	}
}
ll sum(int x){
	ll res=0;
	while(x>0){
		res+=D[x];
		x-=lowbit(x);
	}
	return res;
}

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%lld %lld",&cow[i].vol,&cow[i].loc);
		cow[i].id=i;
		dis[i]=cow[i].loc;
	}
	sort(dis+1,dis+N+1);
	ll old=0;
	memset(D,0,sizeof(D));
	for(int i=1;i<=N;i++){
		update(i,dis[i]-old);
		old=dis[i];
	}
	return 0;
}
