#include<iostream>
#include<stack>
using namespace std;

stack<char> sc;
int main(){
	string s;
	cin>>s;
	bool flag=true;
	for(int i=0;i<s.size();i++){
		if(s[i]=='@') break;
		if(s[i]=='(') sc.push('(');
		if(s[i]==')'){
			if(sc.empty()||sc.top()!='('){
				flag=false;
				break;
			}else{
				sc.pop();
			}
		}
	}
	if(!flag||!sc.empty()){
		printf("NO\n");
	}else{
		printf("YES\n");
	}
	return 0;
}
