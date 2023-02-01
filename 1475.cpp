#include<iostream>
#include<cstdio>
#include<queue>
#include<string>
#include<cstring>
using namespace std;
const int max_n=25;
char maze[max_n][max_n];
bool vis[max_n][max_n];
int R,C;
int Sr,Sc,Br,Bc,Tr,Tc;
string ans;
struct Person{
	int pr,pc;
	string path;
	Person(int _pr,int _pc,string _path){pr=_pr;pc=_pc;path=_path;}
};
struct Box{
	int pr,pc;
	int br,bc;
	string path;
	Box(int _pr,int _pc,int _br,int _bc,string _path){pr=_pr;pc=_pc;br=_br;bc=_bc;path=_path;}
};

int dr[4]={-1,0,1,0};
int dc[4]={0,1,0,-1};
string BPath="NESW";
string PPath="nesw";
bool check(int r,int c){
	if(r<0||r>=R||c<0||c>=C) return false;
	if(maze[r][c]=='#') return false;
	return true;
}
bool bfs2(int bpr,int bpc,int bbr,int bbc,int pr,int pc,string& path){
	bool vis1[max_n][max_n];
	memset(vis1,0,sizeof(vis1));
	queue<Person> qp;
	string ppath="";
	qp.push(Person(bpr,bpc,ppath));
	vis1[bpr][bpc]=1;
	vis1[bbr][bbc]=1;
	while(!qp.empty()){
		Person p=qp.front();
		qp.pop();
		if(p.pr==pr&&p.pc==pc){
			path=p.path;
			return true;
		}
		for(int i=0;i<4;i++){
			int x=p.pr+dr[i];
			int y=p.pc+dc[i];
			if(check(x,y)&&!vis1[x][y]){
				qp.push(Person(x,y,p.path+PPath[i]));
				vis1[x][y]=1;
			}
		}
	}
	return false;
}
bool bfs1(){
	queue<Box> qb;
	memset(vis,0,sizeof(vis));
	qb.push(Box(Sr,Sc,Br,Bc,""));
	vis[Br][Bc]=1;
	while(!qb.empty()){
		Box box=qb.front();
		qb.pop();
		for(int i=0;i<4;i++){
			int br=box.br+dr[i];
			int bc=box.bc+dc[i];
			int pr=box.br-dr[i];
			int pc=box.bc-dc[i];
			string subpath="";
			if(check(br,bc)&&check(pr,pc)&&!vis[br][bc]){
				if(bfs2(box.pr,box.pc,box.br,box.bc,pr,pc,subpath)){
					if(br==Tr&&bc==Tc){
						ans=box.path+subpath+BPath[i];
						return true;
					}
					vis[br][bc]=1;
					qb.push(Box(box.br,box.bc,br,bc,box.path+subpath+BPath[i]));
				}
			}
		}
	}
	return false;
}
int main(){
	int case_num=1;
	while(scanf("%d %d",&R,&C)!=EOF){
		if(R==0&&C==0) break;
		for(int i=0;i<R;i++){
			scanf("%s",maze[i]);
			for(int j=0;j<C;j++)
			{
				if(maze[i][j]=='S'){
					Sr=i;
					Sc=j;
				}
				if(maze[i][j]=='B'){
					Br=i;
					Bc=j;
				}
				if(maze[i][j]=='T'){
					Tr=i;
					Tc=j;
				}
			}
				
		}
		
		//cout<<"Maze #"<<case_num++<<endl;
		printf("Maze #%d\n",case_num++);
		if(bfs1()){
			printf("%s\n\n",ans.c_str());
			//cout<<ans<<endl<<endl;
		}else{
			printf("Impossible.\n\n");
			//cout<<"Impossible."<<endl<<endl;
		}
	}
}

