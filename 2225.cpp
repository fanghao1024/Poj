#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

const int max_n=13;
int dir[6][3]={{1,0,0},{0,1,0},{0,0,1},{-1,0,0},{0,-1,0},{0,0,-1}};
char matrix[max_n][max_n][max_n];
bool vis[max_n][max_n][max_n];
char ch[20];
int N;
int sc,sr,ss,ec,er,es;
struct Node{
	int c,r,s;
	int d;
	Node(){};
	Node(int _c,int _r,int _s,int _d){
		c=_c;r=_r;s=_s;d=_d;
	}
};
bool check(int c,int r,int s){
	if(r<0||r>=N||c<0||c>=N||s<0||s>=N) return false;
	return true;
}
void bfs(){
	memset(vis,0,sizeof(vis));
	queue<Node> q;
	q.push(Node(sc,sr,ss,0));
	vis[sc][sr][ss]=1;
	bool flag=false;
	int ans=-1;
	while(!q.empty()){
		Node node=q.front();
		q.pop();
		if(node.r==er&&node.c==ec&&node.s==es){
			flag=true;
			ans=node.d;
			break;
		}
		for(int i=0;i<6;i++){
			int nr=node.r+dir[i][0],nc=node.c+dir[i][1],ns=node.s+dir[i][2];
			if(check(nc,nr,ns)&&!vis[nc][nr][ns]&&matrix[ns][nr][nc]=='O'){
				vis[nc][nr][ns]=1;
				q.push(Node(nc,nr,ns,node.d+1));
			}
		}
	}
	if(flag){
		printf("%d %d\n",N,ans);
	}else{
		printf("NO ROUTE\n");
	}
}
int main(){
	while(cin.getline(ch,100)){
		int temp=0;
		int len=strlen(ch);
		for(int i=6;i<len;i++){
			temp=temp*10+ch[i]-'0';
		}		
		N=temp;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				scanf("%s",matrix[i][j]);
			}
		}

		scanf("%d %d %d %d %d %d",&sc,&sr,&ss,&ec,&er,&es);
		scanf("%s",ch);
		bfs();
		cin.getline(ch,100);
		//gets(ch);
	}
	return 0;
}

