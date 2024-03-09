#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int max_n=110;
const int inf=0x3f3f3f;
int direction[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
int N;
bool flag;
char ch[max_n][max_n];
bool vis[max_n][max_n];
int sr,sc,er,ec,ans;
bool check(int r,int c){
	if(r<0||r>=N||c<0||c>=N) return false;
	return true;
}
void dfs(int r,int c,int dep,int dir){
	if(r==er&&c==ec){
		if(dep<ans){
			flag=true;
			ans=dep;
		}
		return ;
	}
	if(dep>=ans) return ;
	for(int i=0;i<4;i++){
		int nr=r+direction[i][0];
		int nc=c+direction[i][1];
		if(check(nr,nc)&&ch[nr][nc]!='x'&&!vis[nr][nc]){
			vis[nr][nc]=1;
			int f=0;
			if(i!=dir) f=1;
			if(dir<0) f=0;
			dfs(nr,nc,dep+f,i); 
			vis[nr][nc]=0;
		}
	}
}
int main(){
	cin>>N;
	for(int i=0;i<N;i++){
		
		for(int j=0;j<N;j++){
			cin>>ch[i][j];
			if(ch[i][j]=='A'){
				sr=i;
				sc=j;
			}
			if(ch[i][j]=='B'){
				er=i;
				ec=j;
			}
		}
	}
	ans=inf;
	vis[sr][sc]=1;
	flag=false;
	dfs(sr,sc,0,-100);
	if(flag) cout<<ans<<endl;
	else cout<<"-1"<<endl;
	return 0;
}
