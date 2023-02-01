#include<stdio.h>
#include<iostream>
#include<string>
#include<stack>
#include<map>
#include<algorithm>
using namespace std;

typedef pair<int,int> P;
map<char,P> mcp;
stack<P> sp;
string s;
int main(){
	int N;
	cin>>N;
	char ch;
	int x,y;
	for(int i=0;i<N;i++){
		cin>>ch>>x>>y;
		mcp[ch]=make_pair(x,y);
	}
	while(cin>>s){
		while(!sp.empty()) sp.pop();
		bool flag=true;
		long long ans=0;
		for(int i=0;i<s.size();i++){
			if(s[i]>='A'&&s[i]<='Z'){
				sp.push(mcp[s[i]]);
			}else{
				if(s[i]==')'){
					P p1=sp.top();
					sp.pop();
					P p2=sp.top();
					sp.pop();
					if(p1.first!=p2.second){
						flag=false;
						break;
					}else{
						ans+=p1.second*p2.first*p2.second;
						sp.push(make_pair(p2.first,p1.second));
					}
				}
			}
		}
		//cout<<flag<<" "<<sp.size()<<endl;
		if(flag&&sp.size()==1){
			cout<<ans<<endl;
		}else{
			cout<<"error"<<endl;
		}
	}
	
	return 0;
}
