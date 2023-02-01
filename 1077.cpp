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
char dirname[4]={'d','r','u','l'};
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
void astar(int posx){
	priority_queue<Node> pqn;
	pqn.push(Node(posx,0,dis(rec),cantor(rec),rec));
	vis[cantor(rec)]=1;
	while(!pqn.empty()){
		Node node=pqn.top();
		pqn.pop();
		int temp[max_l];
		
		for(int j=0;j<Len;j++){
			temp[j]=node.rec[j];
		}
		
		for(int i=0;i<4;i++){
			
			int prow=node.pos/3+dx[i];
			int pcol=node.pos%3+dy[i];
			int pos=prow*3+pcol;
			if(prow<0||prow>2||pcol<0||pcol>2) continue;

			swap(temp[node.pos],temp[pos]);
			int c_k=cantor(temp);
			if(!vis[c_k]){
				int hdis=dis(temp);
				pqn.push(Node(pos,node.dep+1,hdis,c_k,temp));
				vis[c_k]=1;
				pre[c_k]=node.cantor_num;
				ans[c_k]=dirname[i];
				if(c_k==0) return;
			}
			swap(temp[node.pos],temp[pos]);

		}
	}
	return ;
}
void show(int u){
	if(pre[u]!=-1){
		show(pre[u]);
		cout<<ans[u];	
	}
	return;
}
int main(){
	int posx;
	jiecheng[0]=1;
	jiecheng[1]=1;
	for(int i=2;i<=Len;i++){
		jiecheng[i]=i*jiecheng[i-1];
	}
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
			astar(posx);
			show(0);
			cout<<endl;
		}else{
			cout<<"unsolvable"<<endl;
		}
	}
	
	return 0;
}

