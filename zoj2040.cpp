#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;

const int max_n=1e4+10;
string s[max_n];
string str;
int cnt;
bool cmp(string s1,string s2){
	int l1=s1.size(),l2=s2.size();
	int i=0;
	if(l1==l2){
		while(i<l1&&s1[i]==s2[i]) i++;
		while(++i<l1){
			if(s1[i]!=s2[i]) return false;
		}
		
	}
	else if(l1==l2+1){
		while(i<l2&&s1[i]==s2[i]) i++;
		while(++i<l1){
			if(s1[i]!=s2[i-1]) return false;
		}
	}
	else if(l1+1==l2){
		while(i<l1&&s1[i]==s2[i]) i++;
		while(++i<l2){
			if(s1[i-1]!=s2[i]) return false;
		}
	}
	else return false;
	return true;
}
int main(){
	int T,kase=0;
	cin>>T;
	while(T--){
		cnt=0;
		while(cin>>s[cnt++]){
			if(s[cnt-1][0]=='#'){
				cnt--;
				break;
			}
		}
		sort(s,s+cnt);
		if(kase++) cout<<endl;
		while(cin>>str){
			if(str[0]=='#') break;
			bool flag=false;
			for(int i=0;i<cnt;i++){
				if(s[i]==str){
					flag=true;
					cout<<str<<" is correct"<<endl;
					break;
				}
			}
			if(!flag){
				cout<<str<<":";
				int mm=0;
				for(int i=0;i<cnt;i++){
					if(cmp(s[i],str)) {cout<<" "<<s[i];}
				}
				cout<<endl;
			}
		}
	}
	return 0;
}
