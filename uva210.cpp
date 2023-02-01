#include <iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<queue>
using namespace std;

int N,t1,t2,t3,t4,t5,Q;
deque<int> q;
queue<int> temp;
int value[30];
vector<string> vs[1010];
int pos[1010];
bool isB;

int main() {
	int T;
	cin>>T;
	while(T--){
		cin>>N>>t1>>t2>>t3>>t4>>t5>>Q;
		memset(value,0,sizeof(value));
		memset(pos,0,sizeof(pos));
		string s;
		q.clear();
		isB=false;
		while(!temp.empty()){
			temp.pop();
		}
		getline(cin, s);
		for(int i=0;i<N;i++){
			vs[i].clear();
			q.push_back(i);
			while(getline(cin, s)){
				vs[i].push_back(s);
				if(s=="end"){
					break;
				}
				
			}
		}
		while(!q.empty()){
			int item=q.front();
			q.pop_front();
			int t=0,v;
			bool flag=true;
			while(t<Q){
				int pp=pos[item];
				pos[item]++;
				string ps=vs[item][pp];
				//cout<<item<<"######"<<ps<<"-----"<<ps[2]<<endl;
				switch(ps[2]){
					case '='://a = 1
						v=ps[4]-'0';
						if(ps.size()==6){
							v=10*v+ps[5]-'0';
						}
						value[ps[0]-'a']=v;
						t+=t1;
						break;
					case 'i'://print
						cout<<item+1<<": "<<value[ps[6]-'a']<<endl;
						t+=t2;
						break;
					case 'c': //lock
						if(!isB){
							isB=true;
						}else{
							temp.push(item);
							pos[item]--;
							flag=false;
						}
						t+=t3;
						break;
					case 'l': //unlock
						if(!temp.empty()){
							int tt=temp.front();
							q.push_front(tt);
							temp.pop();
						}
						isB=false;
						t+=t4;
						break;
					case 'd'://end
						flag=false;
						t+=t5;
						break;
				}
				if(!flag) break;
			}
			if(flag){
				q.push_back(item);
			}
		}
	if(T) cout<<endl;
		
	}
	return 0;
}