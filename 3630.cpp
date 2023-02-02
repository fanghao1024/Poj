#include<string>
#include<iostream>
#include<cstring>
using namespace std;

const int max_n=110010;
int trie[max_n][10];
int End[max_n];
int cnt;
bool add_trie(string s){
	int p=0;
	for(int i=0;i<s.size();i++){
		if(End[p]){
			
			return true;
		}
		int c=s[i]-'0';
		if(!trie[p][c]){
			trie[p][c]=cnt++;
		}else{
			if(i==s.size()-1)
				return true;
		}
		p=trie[p][c];
	}
	if(End[p]) return true;
	
	End[p]=1;
	
	return false;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		memset(End,0,sizeof(End));
		memset(trie,0,sizeof(trie));
		cnt=1;
		int k;
		string s;
		bool flag=false;
		cin>>k;
		for(int i=0;i<k;i++){
			cin>>s;
			if(flag) continue;
			if(add_trie(s)){
				flag=true;
				
			}
				
				
		}
		if(flag){
			cout<<"NO"<<endl;
		}else{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
