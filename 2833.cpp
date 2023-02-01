#include <iostream>
#include<queue>
#include<stdio.h>
#include<functional>
using namespace std;

typedef long long ll;
int main(int argc, char *argv[]) {
	int n1,n2,n;
	while(scanf("%d %d %d",&n1,&n2,&n)){
		if(n1==0&&n2==0&&n==0) break;
		ll sum=0;
		ll num;
		priority_queue<ll> pl;
		priority_queue<ll,vector<ll>,greater<ll> > pg;
		int nn=n;
		while(nn--){
			scanf("%lld",&num);
			sum+=num;
			pl.push(num);
			pg.push(num);
			if(pl.size()>n2) pl.pop();
			if(pg.size()>n1) pg.pop();
		}
		//printf("%d\n",sum);
		while(!pg.empty()){
			sum-=pg.top();
			//printf("%d\n",sum);
			pg.pop();
		}
		while(!pl.empty()){
			sum-=pl.top();
			//printf("%d\n",sum);
			pl.pop();
		}
		printf("%.6f\n",1.0*sum/(n-n1-n2));
	}
	return 0;
}