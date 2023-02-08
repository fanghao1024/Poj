#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int cantor_num=362890;
const int max_l=12;
bool vis[cantor_num];
char ans[cantor_num];
char inputs[max_l];
int pre[cantor_num];
char ch[max_l];
int rec[max_l];
int jiecheng[max_l];
const int Len=9;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
//char dirname[4]={'u','r','d','l'};
char dirname[]="drul";
struct Node{
	int pos;
	int dep;
	int cost;
	int f;
	int cantor_num;
	int rec[12];
	Node(){};
	Node(int _pos,int _dep,int _cost,int _cantor,int _rec[]){
		pos=_pos;
		dep=_dep;
		cost=_cost;
		f=_dep+_cost;
		cantor_num=_cantor;
		for(int i=0;i<Len;i++){
			rec[i]=_rec[i];
		}
	}
	bool operator<(const Node& a) const{
		return f>a.f;
	}
};
Node nxt;
int cantor(int num[]){
	int res=0;
	for(int i=0;i<Len;i++){
		int count=0;
		for(int j=i+1;j<Len;j++){
			if(num[i]>num[j]) count++;
		}
		res+=count*jiecheng[Len-1-i];
	}
	return res;
}

bool order(int num[]){
	int ans=0;
	for(int i=0;i<Len;i++){
		if(num[i]==Len-1) continue;
		for(int j=i+1;j<Len;j++){
			if(num[i]>num[j]) ans++;
		}
	}
	if(ans%2==0) return true;
	return false;
}
int dis(int num[]){
	int res=0;
	for(int i=0;i<Len;i++){
		if(num[i]==Len-1) continue;
		res+=abs(num[i]/3-i/3)+abs((num[i]%3)-(i%3));
	}
	return res;
}

int dep;
char idastar[cantor_num];
bool dfs(int pos,int d,int pre){
	int h=dis(rec);
	if(!h){
		idastar[d]='\0';
		return true;
	}
	if(d+h>dep) return false;
	for(int i=0;i<4;i++){
		int prow=pos/3+dx[i];
		int pcol=pos%3+dy[i];
		int npos=prow*3+pcol;
		if(prow<0||prow>2||pcol<0||pcol>2||npos==pre) continue;
		swap(rec[pos],rec[npos]);
		idastar[d]=dirname[i];
		if(dfs(npos,d+1,pos)) return true;
		swap(rec[pos],rec[npos]);
	}
	return false;
}
void Idastar(int posx){
	dep=0;
	while(++dep){
		if(dfs(posx,0,-1)) break;
	}
}


int main(){
	int posx;
	while(scanf("%s",inputs)!=EOF){
		if(inputs[0]>'0'&&inputs[0]<'9'){
			rec[0]=inputs[0]-'1';
		}else{
			if(rec[0]=='x'){
				rec[0]=Len-1;
				posx=0;
			}
		}
		for(int i=1;i<Len;i++){
			scanf("%s",inputs);
			if(inputs[0]>'0'&&inputs[0]<'9'){
				rec[i]=inputs[0]-'1';
			}else{
				if(inputs[0]=='x'){
					rec[i]=8;
					posx=i;
				}
			}
		}
		
		if(order(rec)){
			memset(vis,0,sizeof(vis));
			memset(pre,-1,sizeof(pre));
			Idastar(posx);
			cout<<idastar<<endl;
		}else{
			cout<<"unsolvable"<<endl;
		}
	}
	
	return 0;
}

