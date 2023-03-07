#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#include<iostream>
using namespace std;

typedef pair<int,int> P;
const int max_n=210;
const int inf=0x3f3f3f;
int direction[4][2]={{0,-1},{1,0},{0,1},{-1,0}};
int N;
char ch[max_n][max_n];
bool vis[max_n][max_n];
int dep[max_n][max_n];
int sr,sc,er,ec,ans;
bool check(int r,int c){
	if(r<0||r>=N||c<0||c>=N) return false;
	return true;
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
				ch[i][j]='.';
			}
		}
	}
	memset(dep,-1,sizeof(dep));
	vis[sr][sc]=1;
	//dep[sr][sc]=-1;
	queue<P> q;
	q.push(make_pair(sr,sc));
	bool flag=false;
	while(!q.empty()){
		P p=q.front();
		q.pop();
		if(p.first==er&&p.second==ec){
			flag=true;
			break;
		}
		
		for(int i=0;i<4;i++){
			int nr=p.first,nc=p.second;
			while(check(nr+direction[i][0],nc+direction[i][1])&&ch[nr+direction[i][0]][nc+direction[i][1]]=='.'
				&&!vis[nr+direction[i][0]][nc+direction[i][1]]){
				nr+=direction[i][0];
				nc+=direction[i][1];
				dep[nr][nc]=dep[p.first][p.second]+1;
				vis[nr][nc]=1;
				q.push(make_pair(nr,nc));
			}
		}
	}
	if(flag) printf("%d\n",dep[er][ec]);
	else printf("-1\n");
	return 0;
}
