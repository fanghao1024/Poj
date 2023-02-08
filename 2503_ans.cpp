/*
#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
using namespace std;
const int maxn=500005;
const int maxz=26;//不同字符个数，例如数字10，小写字母26
int trie[maxn][maxz];
char word[maxn][15];//翻译单词 
int value[maxn];//值的下标
bool End[maxn];//标记结束 
int n,tot;//字符串数,下标 
char w[20],w1[20];
void insert(char s[],int k){//将字符串s插入到字典树中 
	int len=strlen(s),p=1;
	for(int i=0;i<len;i++){
		int ch=s[i]-'a';//转换成数字
		if(!trie[p][ch]) 
			trie[p][ch]=++tot;//记录下标 
		p=trie[p][ch];
	}
	value[p]=k;//记录下标
	End[p]=1; 
}

int query(char w[]){
	int p=1;
	for(int i=0;i<strlen(w);i++){
		int ch=w[i]-'a';//转换成数字
		p=trie[p][ch];
		if(!p)
			return 0;
	}
	if(End[p])
		return value[p];//返回下标 
	return 0;	
}

int main(){	
	string s,s1;
	memset(trie,0,sizeof(trie));
	tot=1;
	int i=1;
	while(gets(w)){
	//while(getline(cin,s)){
		if(!strlen(w))
			break;
		int ls=0;
		while(w[ls]!=' ') ls++;
		strncpy(word[i++],w,ls);
		strncpy(w1,w+ls,strlen(w)-ls);
		insert(w1,i);
		i++;
	}
	while(scanf("%s",w)!=EOF){
		//while(cin>>s){
		
		int k=query(w);
		if(k)
			cout<<word[k]<<endl;
		else
			cout<<"eh"<<endl;
	}
	return 0;
}
 */
#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=800005;
const int maxz=26;//不同字符个数，例如数字10，小写字母26
int trie[maxn][maxz];
string word[maxn];//翻译单词 
int value[maxn];//值的下标
bool End[maxn];//标记结束 
int n,tot;//字符串数,下标 
char w[12];
void insert(string s,int k){//将字符串s插入到字典树中 
	int len=s.length(),p=1;
	for(int i=0;i<len;i++){
		int ch=s[i]-'a';//转换成数字
		if(!trie[p][ch]) 
			trie[p][ch]=++tot;//记录下标 
		p=trie[p][ch];
	}
	value[p]=k;//记录下标
	End[p]=1; 
}

int query(char w[]){
	int p=1;
	for(int i=0;i<strlen(w);i++){
		int ch=w[i]-'a';//转换成数字
		p=trie[p][ch];
		if(!p)
			return 0;
	}
	if(End[p])
		return value[p];//返回下标 
	return 0;	
}

int main(){	
	string s,s1;
	memset(trie,0,sizeof(trie));
	tot=1;
	int i=1;
	while(getline(cin,s)){
		if(!s.size())
			break;
		stringstream ss(s);
		ss>>word[i]>>s1;
		insert(s1,i);
		i++;
	}
	while(scanf("%s",w)!=EOF){
		//while(cin>>s){
		
		int k=query(w);
		if(k)
			//cout<<word[k]<<endl;
			printf("%s\n",word[k].c_str());
		else
			printf("eh\n");
		//cout<<"eh"<<endl;
	}
	return 0;
}
