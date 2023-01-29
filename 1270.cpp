#include<iostream>
#include<string>
#include<string.h>
#include<map>
#include<algorithm>
using namespace std;


const int max_n=30;
char ch[max_n];
int degree[max_n];
bool path[max_n][max_n];
bool vis[max_n];
int rec[max_n];
void show(int l,int index){
	if(l==index){
		for(int i=0;i<index;i++){
			printf("%c",ch[rec[i]]);
		}
		printf("\n");
	}
	else{
		for(int i=0;i<index;i++){
			if(!vis[i]&&!degree[i]){
				vis[i]=1;
				rec[l]=i;
				for(int j=0;j<index;j++){
					if(path[i][j]){
						degree[j]--;
					}
				}
				show(l+1,index);
				for(int j=0;j<index;j++){
					if(path[i][j]){
						degree[j]++;
					}
				}
				vis[i]=0;
			}
		}
	}
	
}
int main(){
	string s;
	int counts=0;
	while(getline(cin,s)){
		int index=0;
		map<char,int> mci;
		for(int i=0;i<s.size();i++){
			if(s[i]!=' '){
				ch[index]=s[i];
				index++;
			}
		}
		sort(ch,ch+index);
		for(int i=0;i<index;i++){
			mci[ch[i]]=i;
		}
		getline(cin,s);
		int id=0;
		char x,y;
		memset(degree,0,sizeof(degree));
		memset(path,0,sizeof(path));
		memset(vis,0,sizeof(vis));
		for(int i=0;i<s.size();i++){
			if(s[i]!=' '&&id==0){
				x=s[i];
				id=1;
			}else{
				if(s[i]!=' '&&id==1){
					y=s[i];
					id=0;
					path[mci[x]][mci[y]]=1;
					degree[mci[y]]++;
				}
			}
		}
		if(counts++) printf("\n");
		show(0,index);
	}
	return 0;
}
