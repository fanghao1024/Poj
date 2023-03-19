#include<string>
#include<iostream>
#include<map>
using namespace std;
map<string,int> ssi;

int main(){
	int N,M;
	string s;
	scanf("%d",&N);
	while(N--){
		cin>>s;
		ssi[s]=1;
	}
	scanf("%d",&M);
	while(M--){
		cin>>s;
		if(!ssi[s]) cout<<"WRONG"<<endl;
		else if(ssi[s]==1){cout<<"OK"<<endl;ssi[s]++;}
		else cout<<"REPEAT"<<endl;
	}
	return 0;
}
