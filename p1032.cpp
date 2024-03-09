#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

string s[2];
map<string,int> msi[2];
string m[2][6];
queue<string> q[2];
bool flag;
int ans,cnt;
void extend(int index){
	string str=q[index].front();
	q[index].pop();
	//cout<<str<<endl;
	if(msi[1-index][str]!=0){
		if(msi[index][str]+msi[1-index][str]<=12){
			flag=true;
			ans=msi[index][str]+msi[1-index][str]-2;
			return ;
		}
		
	}
	if(msi[index][str]<=10){
		for(int i=0;i<cnt;i++){
			int pos,j,k;
			
			for(j=0;j<str.length();j++){
				bool ok=true;
				if(str.length()-j<m[index][i].length())
					break;
				for(k=0;k<m[index][i].length();k++){
					if(str[j+k]!=m[index][i][k]){
						ok=false;
						break;
					}
				}
				if(ok){
					string temp=str.substr(0,j);
					temp+=m[1-index][i];
					temp+=str.substr(j+m[index][i].length());
					if(msi[index][temp]==0){
						msi[index][temp]=msi[index][str]+1;
						q[index].push(temp);
						//cout<<"add:"<<temp<<endl;
					}
					
				}
			}
		}
	} 
	
	
}
void bfs(){
	q[0].push(s[0]);
	msi[0][s[0]]=1;
	q[1].push(s[1]);
	msi[1][s[1]]=1;
	while(q[0].size()&&q[1].size()){
		if(q[0].size()<q[1].size()) extend(0);
		else extend(1);
		if(flag) break;
	}
}
int main(){
	cin>>s[0]>>s[1];
	string str1,str2;
	cnt=0;
	while(cin>>str1>>str2){
		//if(str1=="0") break;
		m[0][cnt]=str1;
		m[1][cnt]=str2;
		cnt++;
	}
	flag=false;
	bfs();
	if(flag) printf("%d\n",ans);
	else printf("NO ANSWER!\n");
	return 0;
}
