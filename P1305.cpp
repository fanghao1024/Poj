#include <iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;

string ss[26];
int N;
map<char,string> mcs;

void process(char i){
	cout<<i;
	if(mcs[i][0]!='*'){
		process(mcs[i][0]);
	}
	if(mcs[i][1]!='*'){
		process(mcs[i][1]);
	}
}
int main() {
	cin>>N;
	for(int i=0;i<N;i++){
		cin>>ss[i];
		mcs[ss[i][0]]=ss[i].substr(1,2);
		//cout<<mcs[ss[i][0]]<<endl;
	}
	
	process(ss[0][0]);
	return 0;
}