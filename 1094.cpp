#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<stack>
using namespace std;

int N,M;
const int max_n=30;
int map[max_n][max_n];
int degree[max_n];
int temp[max_n];
int rec[max_n];
int toposort(int n){
	int count=0;
	int pos;
	int m=0;
	int flag=1;
	stack<int> si;
	for(int i=1;i<=n;i++){
		temp[i]=degree[i];
		if(temp[i]==0){
			count++;
			si.push(i);
		}
	}
	if(count==0) return -1;//有环
	if(count>1) flag=0;//不确定
	while(!si.empty()){
		pos=si.top();
		si.pop();
		rec[++m]=pos;
		count=0;
		for(int i=1;i<=n;i++){
			if(map[pos][i]){
				temp[i]--;
				if(!temp[i]){
					si.push(i);
					count++;
				}
			}
		}
		
		if(count>1) flag=0;
	}
	if(m<n) return -1;
	return flag;
}

int main(){
	while(cin>>N>>M){
		if(N==0&&M==0) break;
		memset(map,0,sizeof(map));
		memset(degree,0,sizeof(degree));
		string s;
		int flag=0;
		for(int i=1;i<=M;i++){
			cin>>s;
			if(flag) continue;
			int x=s[0]-'A'+1;
			int y=s[2]-'A'+1;
			map[x][y]=1;
			degree[y]++;
			int res=toposort(N);
			if(res==-1){
				flag=1;
				printf("Inconsistency found after %d relations.\n",i);
			}else{
				if(res==1){
					flag=1;
					printf("Sorted sequence determined after %d relations: ",i);
					for(int j=1;j<=N;j++) printf("%c",char('A'+rec[j]-1));
					printf(".\n");
				}
			}
		}
		if(!flag){
			printf("Sorted sequence cannot be determined.\n");
		}
	}
	return 0;
}
