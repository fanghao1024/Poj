#include<iostream>
#include<string>
#include<string.h>
using namespace std;

string s1,s2;
const int max_n=1000010;
int Next[max_n];

void getNext(){
	Next[0]=-1;
	int j=0;
	int k=-1;
	while(j<s2.size()){
		if(k==-1||s2[j]==s2[k]){
			Next[++j]=++k;
		}else{
			k=Next[k];
		}
	}
}
void KMP(){
	int i=0,j=0;
	while(i<s1.size()){
		if(j==-1||s1[i]==s2[j]){
			i++;
			j++;
		}else{
			j=Next[j];
		}
		if(j==s2.size()){
			cout<<i-j+1<<endl;
			j=Next[j];
		}
	}
}
int main(){
	cin>>s1>>s2;
	getNext();
	KMP();
	for(int i=1;i<=s2.size();i++){
		if(i-1) cout<<" ";
		cout<<Next[i];
	}
	cout<<endl;
}
