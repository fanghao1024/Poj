#include<cstdio>
#include<cstring>
#include<iostream>
#include<sstream>
using namespace std;

const int max_n=100005*5;
char eng_words[100005][13];
int cnt;
int word_cnt;
char words[30];
char words1[30];
int fore_words[max_n][26];
int End[max_n];

void add_words(char w[],int l){
	int p=0;
	for(int i=0;i<l;i++){
		
		int c=w[i]-'a';
		if(!fore_words[p][c]){
			fore_words[p][c]=cnt++;
		}
		p=fore_words[p][c];
		
	}
	
	End[p]=word_cnt;
}
int find(string ch){
	int p=0;
	for(int i=0;i<ch.size();i++){
		int c=ch[i]-'a';
		
		if(!fore_words[p][c]){
			return -1;
		}
		p=fore_words[p][c];
	}
	
	return End[p];
}
int main(){
	cnt=0;
	word_cnt=0;
	memset(End,-1,sizeof(End));
	memset(fore_words,0,sizeof(fore_words));
	string s;
	
	while(getline(cin,s)){
		if(!s.size()) break;
		stringstream ss(s);
		ss>>words>>words1;
		
		strcpy(eng_words[word_cnt],words);
		add_words(words1,strlen(words1));
		word_cnt++;
	}
	while(cin>>s){
		int index=find(s);
		if(index==-1){
			printf("eh\n");
		}else{
			printf("%s\n",eng_words[index]);
		}
	}
	return 0;
}
