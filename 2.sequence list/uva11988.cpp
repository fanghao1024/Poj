#include<list>
#include<iostream>
using namespace std;

int main(){
	string s;
	while(cin>>s){
		list<char> lc;
		list<char>::iterator it=lc.begin();
		for(int i=0;i<s.size();i++){
			if(s[i]=='['){
				it=lc.begin();
			}else{
				if(s[i]==']'){
					it=lc.end();
				}else{
					lc.insert(it,s[i]);
				}
			}
		}
		for(it=lc.begin();it!=lc.end();it++){
			cout<<*it;
		}
		cout<<endl;
	}
	return 0;
}
