#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<map>
#include<string>
using namespace std;

map<string,int> msi;

int main(){
	int ans=0;
	string s;
	while(getline(cin,s)){
		msi[s]++;
		ans++;
	}
	for(map<string,int>::iterator it=msi.begin();it!=msi.end();it++){
		cout<<it->first<<" ";
		printf("%.4f\n",100.0*(it->second)/ans);
	}
	
	return 0;
}
