#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;

ll extE(ll a,ll b,ll& x ,ll& y){
	if(b==0){x=1;y=0;return a;}
	else{
		ll d=extE(b,a%b,y,x);
		y-=(a/b)*x;
		return d;
	}
}
int main(){
	ll x,y,m,n,L;
	cin>>x>>y>>m>>n>>L;
	ll a=n-m,c=x-y;
	if(a<0){a=-a;c=-c;}
	ll d=extE(a,L,x,y);
	if(c%d) cout<<"Impossible"<<endl;
	else cout<<((x*(c/d))%(L/d)+L/d)%(L/d)<<endl;
	return 0;
}
