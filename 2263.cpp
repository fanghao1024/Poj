#include <iostream>
#include<cmath>
using namespace std;

struct Pos{
	int x,y;
}pos[1010];
bool dis[1010][1010];
double distance(int i,int j){
	return sqrt(pow(pos[i].x-pos[j].x+0.0,2)+pow(pos[i].y-pos[j].y+0.0,2));
}
int par[1010];
int ranks[1010];
void init(int n){
	for(int i=0;i<n;i++){
		par[i]=-1;
		ranks[i]=1;
	}
}
int find(int x){
	if(par[x]==x){
		return x;
	}
	return par[x]=find(par[x]);
}
void unite(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y) return;
	if(ranks[x]>ranks[y]){
		par[y]=x;
	}else{
		par[x]=y;
		if(ranks[x]==ranks[y]){
			ranks[y]++;
		}
	}
}
bool same(int x,int y){
	return find(x)==find(y);
}

int main() {
	int N,d;
	cin>>N>>d;
	for(int i=0;i<N;i++){
		//scanf("%d %d",&pos[i].x,&pos[i].y);
		cin>>pos[i].x>>pos[i].y;
	}
	for(int i=0;i<N;i++){
		dis[i][i]=1;
		for(int j=i+1;j<N;j++){
			//cout<<i<<" "<<j<<" "<<distance(i, j)<<endl;
			dis[i][j]=dis[j][i]=distance(i,j)<=d;
		}
	}

	init(N);
	char ch;
	int x,y;
	while(cin>>ch){
		switch (ch) {
			case 'O':
				cin>>x;
				x=x-1;
				if(par[x]==-1){
					par[x]=x;
				}
				for(int i=0;i<N;i++){
					if(dis[x][i]&&par[i]!=-1){
						unite(x,i);
					}
				}
				break;
			case 'S':
				cin>>x>>y;
				x-=1;
				y-=1;
				//cout<<find(x)<<" "<<find(y)<<endl;
				if(par[x]==-1||par[y]==-1){
					cout<<"FAIL"<<endl;
				}else{
					if(same(x,y)){
						cout<<"SUCCESS"<<endl;
					}else{
						cout<<"FAIL"<<endl;
					}
				}
				
				break;
			
		}
	}
	return 0;
	
}