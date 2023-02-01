#include <iostream>
#include <string>
#include<map>
#include<queue>
#include<vector>
#include<iomanip>
using namespace std;

int main() {
	string s;
	while(cin>>s){
		if(s=="END") break;
		map<char,int> mci;
		for(int i=0;i<s.size();i++){
			mci[s[i]]++;
		}
		priority_queue<int,vector<int>,greater<int> > PQ;
		for(map<char,int>::iterator it=mci.begin();it!=mci.end();it++){
			PQ.push(it->second);
		}
		if(PQ.size()==1){
			printf("%d %d 8.0\n",s.size()*8,s.size());
		}else{
			int ans=0;
			while(PQ.size()>1){
				int first=PQ.top();PQ.pop();
				int second=PQ.top();PQ.pop();
				PQ.push(first+second);
				ans+=first+second;
			}
			printf("%d %d %.1f\n",s.size()*8,ans,double(s.size()*8.0/ans));
		}
		
	}
	return 0;
}