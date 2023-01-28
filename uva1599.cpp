#include<iostream>
#include<string.h>
#include<queue>
#include<string>
#include<map>
using namespace std;

const int max_m=200005;
const int max_n=100005;

int N,M;
int head[max_n];
struct Edge{
	int to,color;
	int nxt;
}edge[max_m];
struct QV{
	int index,dep;
	string s;
	
	QV(int index,int dep,string s){
		this->index=index;
		this->dep=dep;
		this->s=s;
	};
};
int cnt;
bool vis[max_n];
void add_edge(int x,int y,int c){
	edge[cnt].to=y;
	edge[cnt].color=c;
	edge[cnt].nxt=head[x];
	head[x]=cnt;
	cnt++;
}
int main(){
	//while(scanf("%d %d",&N,&M)!=EOF){
	while(cin>>N>>M){
		int x,y,c;
		cnt=0;
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		for(int i=0;i<M;i++){
			cin>>x>>y>>c;
			add_edge(x,y,c);
			add_edge(y,x,c);
		}
		queue<QV> q;
		string s="";
		q.push(QV(1,0,s));
		int curLen=M;
		vis[1]=1;
		string ansstr="";
		while(!q.empty()){
			QV qv=q.front();
			q.pop();
			int index=qv.index;
			int dep=qv.dep;
			s=qv.s;
			if(dep>curLen) break;
			if(index==N){
				if(dep<curLen){
					curLen=dep;
					ansstr=s;
				}else{
					if(dep==curLen){
						if(s<ansstr) ansstr=s;
					}
				}
			}
			for(int i=head[index];i!=-1;i=edge[i].nxt){
				if(!vis[edge[i].to]){
					if(s==""){
						q.push(QV(edge[i].to,dep+1,to_string(edge[i].color)));
					}else{
						q.push(QV(edge[i].to,dep+1,s+" "+to_string(edge[i].color)));
					}
					
				}
			}
		}
		//printf("%d\n",curLen);
		cout<<curLen<<endl;
		cout<<ansstr<<endl;
		
		
	}
	return 0;
}

