#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;

typedef long long ll;
ll N;
void bfs(ll n){
	ll res=1;
	queue<ll> q;
	q.push(res);
	while(!q.empty()){
		ll temp=q.front();
		q.pop();
		if(temp%n!=0){
			q.push(temp*10);
			q.push(temp*10+1);
		}else{
			cout<<temp<<endl;
			return;
		}
	}
}
int main(){
	while(cin>>N){
		if(!N) break;
		bfs(N);
	}
	return 0;
}
