#include<string>
#include<iostream>
using namespace std;

typedef long long ll;
const int max_n=100000;
ll x[max_n],y[max_n],z[max_n];
ll ans;
int cn;

void transtr(string s,int n){
	int i=0;
	ll num=0;
	while(s[i]>='0'&&s[i]<='9'){
		num*=10;
		num+=s[i]-'0';
		i++;
	}
	x[n]=num;
	i++;
	num=0;
	while(s[i]>='0'&&s[i]<='9'){
		num*=10;
		num+=s[i]-'0';
		i++;
	}
	y[n]=num;
	i++;
	num=0;
	while(i<s.size()&&s[i]>='0'&&s[i]<='9'){
		num*=10;
		num+=s[i]-'0';
		i++;
	}
	z[n]=num;
}

ll check(ll mid){
	ll m=0,mm=0;
	for(int i=0;i<cn;i++){
		ll sum=(y[i]-x[i])/z[i]+1;
		if(mid<x[i]){
			mm+=sum;
		}else{
			if(y[i]<mid){
				continue;
			}else{
				if((mid-x[i])%z[i]==0){
					mm+=sum-(mid-x[i])/z[i];
					m++;
				}else{
					mm+=sum-(mid-x[i])/z[i]-1;
				}
			}
		}
	}
	if(mm%2==1){
		ans=mid;
		return m;
	}else{
		return -1;
	}
}
int main(){
	string s;
	while(getline(cin,s)){
		if(s=="") continue;
		cn=0;
		transtr(s,cn++);
		while(getline(cin,s)){
			if(s=="") break;
			transtr(s,cn++);
		}
		ll lb=0;
		ll ub=1LL<<32;
		while(ub>lb+1){
			ll mid=(lb+ub)/2;
			//printf("===%lld\n",mid);
			if(check(mid)==-1){
				ub=mid;
			}else{
				lb=mid;
			}
		}
		if(lb==0){
			printf("no corruption\n");
		}else{
			printf("%lld %lld\n",ans,check(ans));
		}
		
	}
	return 0;
}
