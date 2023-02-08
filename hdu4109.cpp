#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;

const int max_n=1005;
int path[max_n][max_n];
int ve[max_n];
int degree[max_n];
int N,M;
int rec[max_n];
int d[max_n];
void TopoSort(){
	int cnt=0;
	memset(d,0,sizeof(d));
	stack<int> si;
	for(int i=0;i<N;i++){
		if(!degree[i]){
			si.push(i);
			d[i]=1;
		}
	}
	while(!si.empty()){
		int v=si.top();
		si.pop();
		rec[cnt++]=v;
		for(int i=0;i<N;i++){
			if(path[v][i]){
				if(d[i]<d[v]+path[v][i]) d[i]=d[v]+path[v][i];
				if(--degree[i]==0){
					si.push(i);
				}
			}
		}
	}
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		int x,y,z;
		memset(path,0,sizeof(path));
		memset(degree,0,sizeof(degree));
		for(int i=0;i<M;i++){
			scanf("%d %d %d",&x,&y,&z);
			path[x][y]=z;
			degree[y]++;
		}
		TopoSort();
		int ans=0;
		for(int i=0;i<N;i++){
			ans=ans>d[i]?ans:d[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
