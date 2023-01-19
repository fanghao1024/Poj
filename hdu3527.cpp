#include<stdio.h>
#include<vector>
#include<string>
#include<iostream>
#include<set>
using namespace std;
set<string> A,C;
vector<string>B;
int main(){
	int a,b,c;
	while(cin>>a>>b>>c){
		A.clear();
		B.clear();
		C.clear();
		string s;
		while(a--){
			cin>>s;
			A.insert(s);
		}
		while(b--){
			cin>>s;
			B.push_back(s);
		}
		while(c--){
			cin>>s;
			C.insert(s);
		}
		bool flag=false;
		for(vector<string>::iterator it=B.begin();it!=B.end();it++){
			if(A.find(*it)!=A.end()&&C.find(*it)==C.end()){
				if(flag) cout<<" ";
				flag=true;
				cout<<*it;
			}
		}
		
		if(!flag){
			cout<<"No enemy spy"<<endl;
		}else{
			cout<<endl;
		}
	}
	return 0;
}
