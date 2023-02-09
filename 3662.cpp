#include <iostream>
#include<stdio.h>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

typedef int ll;
ll N,P,K;
ll dis[1010][1010];
ll newdis[1010][1010];
const ll Inf=1000000;
typedef pair<ll,ll> PP;
ll record[1010];

int dijstra(){
	priority_queue<PP,vector<PP>,greater<PP> > pq;
	for(int i=1;i<=N;i++) record[i]=Inf;
	record[1]=0;
	pq.push(make_pair(0, 1));
	while(!pq.empty()){
		PP p=pq.top();
		pq.pop();
		int v=p.second;
		int d=p.first;
		if(record[v]<d) continue;
		if(v==N) return d;
		for(int i=1;i<=N;i++){
			if(record[i]>record[v]+newdis[v][i]){
				record[i]=record[v]+newdis[v][i];
				pq.push(make_pair(record[i], i));
			}
		}
	}
	return Inf;
}
bool check(int mid){
	for(int i=1;i<=N;i++){
		for(int j=i;j<=N;j++){
			if(dis[i][j]<=mid){
				newdis[i][j]=newdis[j][i]=0;
			}else{
				if(dis[i][j]<Inf){
					newdis[i][j]=newdis[j][i]=1;
				}else{
					newdis[i][j]=newdis[j][i]=Inf;
				}
			}
		}
	}
	/*
	if(mid<3){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				printf("==%d ",newdis[i][j]);
			}
			printf("\n");
		}
	}
	*/
	ll ans=dijstra();
	//printf("~~~%d\n",ans);
	if(ans<=K){
		return true;
	}else{
		return false;
	}
}

int main() {
	scanf("%d %d %d",&N,&P,&K);
	ll Ai,Bi,Li;
	for(int i=1;i<=N;i++){
		for(int j=i;j<=N;j++){
			if(i!=j){
				dis[i][j]=dis[j][i]=Inf;
			}else{
				dis[i][j]=0;
			}
			
		}
	}
	for(int i=0;i<P;i++){
		scanf("%d %d %d",&Ai,&Bi,&Li);
		dis[Ai][Bi]=Li;
		dis[Bi][Ai]=Li;
	}
	
	ll lb=-1;
	ll ub=1000000;
	while(ub>lb+1){
		ll mid=((ub-lb)>>1)+lb;
		//printf("%d==%d---%d\n",lb,mid,ub);
		if(check(mid)){
			ub=mid;
		}else{
			lb=mid;
		}
	}
	if(lb+1>=1000000){
		printf("-1\n");
	}else{
		printf("%d\n",ub);
	}
	
	return 0;
}