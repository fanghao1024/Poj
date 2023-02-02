#include<iostream>
#include<string>
#include<cstring>
using namespace std;

const int max_n=500005;
int trie[max_n][26];
int counts[max_n];
char word[20];
int cnt;
void add_trie(string s){
	int p=0;
	for(int i=0;i<s.size();i++){
		int c=s[i]-'a';
		if(!trie[p][c]){
			trie[p][c]=cnt++;
		}
		p=trie[p][c];
		counts[p]++;
	}
}
int find(string s){
	int p=0;
	for(int i=0;i<s.size();i++){
		int c=s[i]-'a';
		if(!trie[p][c]) return 0;
		p=trie[p][c];
	}
	return counts[p];
}
int main(){
	string s;
	memset(counts,0,sizeof(counts));
	memset(trie,0,sizeof(trie));
	cnt=1;
	while(getline(cin,s)){
		if(!s.size()) break;
		add_trie(s);
	}
	while(cin>>s){
		cout<<find(s)<<endl;
	}
	return 0;
}
