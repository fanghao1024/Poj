#include<string>
#include<iostream>
#include<cmath>
using namespace std;

typedef long long ll;
ll gcd(ll a,ll b){
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}
int main(){
	string s;
	ll num,up,down,gcd_num;
	while(cin>>s){
		if(s=="0") break;
		num=0;
		for(int i=2;s[i]!='.';i++){
			num*=10;
			num+=s[i]-'0';
		}
		
		int l=s.size()-5;
		ll result_up=100000000000;
		ll result_down=100000000000;
		for(int i=1;i<=l;i++){
			up=num-num/((ll)pow(10.0,i));
			down=((ll)pow(10.0,l-i))*((ll)(pow(10.0,i)-1));
			//cout<<up<<"-"<<down<<"===="<<gcd(up,down)<<endl;
			gcd_num=gcd(up,down);
			//cout<<up/gcd_num<<"////////"<<down/gcd_num<<endl;
			if(result_down>down/gcd_num){
				result_down=down/gcd_num;
				result_up=up/gcd_num;
			}
			
		}
		cout<<result_up<<"/"<<result_down<<endl;
	}
	return 0;
}
