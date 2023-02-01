#include <iostream>
#include <string>
using namespace std;
string s1,s2;

void process(string s1,string s2){
	if(s1.size()==0) return;
	if(s1.size()==1){
		cout<<s1;
		return ;
	}
	//cout<<"###"<<s1<<" "<<s2<<endl;
	char root=s1[0];
	int index=s2.find(root);
	process(s1.substr(1,index),s2.substr(0,index));
	process(s1.substr(index+1,s1.size()-index-1), s2.substr(index+1,s1.size()-index-1));
	cout<<root;
} 

int main() {
	while(cin>>s1>>s2){
		process(s1,s2);
		cout<<endl;
	}
	return 0;
}