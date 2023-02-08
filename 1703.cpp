#include<stdio.h>
#include<iostream>
using namespace std;

const int max_n=200010;
int par[max_n];
int ranks[max_n];
void init(int n){
	for(int i=0;i<n;i++){
		par[i]=i;
		ranks[i]=0;
	}
}
int find(int x){

	if(par[x]==x){
		return x;
	}

	par[x]=find(par[x]);
	return par[x];
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
			ranks[y]+=1;
		}
		
	}
}
bool same(int x,int y){
	return find(x)==find(y);
}

int main(){
	int T,N,M;
	scanf("%d",&T);
	//cin>>T;
	while(T--){
		scanf("%d %d",&N,&M);
		//cin>>N>>M;
		init(N*2+2);
		char ch;
		int a,b;
		if(N==2){
			unite(1,4);
			unite(2,3);
		}
		for(int i=0;i<M;i++){
			scanf(" %c %d %d",&ch,&a,&b);
			//cout<<T<<"==="<<i<<" "<<M<<endl;
			//getchar();
			//scanf("%c",&ch);
			//scanf("%d %d",&a,&b);
			//cin>>ch>>a>>b;
			//printf("%c %d %d\n",ch,a,b);
			//printf("%d-%d\n",par[a],par[b]);
			switch (ch) {
			case 'A':
				if(same(a,b)||same(a+N,b+N)){
					//cout<<"In the same gang."<<endl;
					printf("In the same gang.\n");
				}else{
					if(same(a,b+N)||same(a+N,b)){
						//cout<<"In different gangs."<<endl;
						printf("In different gangs.\n");
					}else{
						//cout<<"Not sure yet."<<endl;
						printf("Not sure yet.\n");
					}
					
				}
				break;
			case 'D':
				unite(a,b+N);
				unite(a+N,b);
				break;
			}
		
		}
	}
	
	return 0;
}
