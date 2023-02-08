#include<stdio.h>
#include<string.h>
#include<queue>
#include<map>
using namespace std;

typedef pair<int,int> P;
const int max_n=100005;
bool vis[max_n];
int N,K;
queue<P> q;
int main(){
	memset(vis,0,sizeof(vis));
	scanf("%d %d",&N,&K);
	if(N==K){
		printf("0\n");
	}
	else{
		q.push(make_pair(N,0));
		vis[N]=1;
		bool flag=false;
		while(!q.empty()){
			P p=q.front();
			q.pop();
			for(int i=0;i<3;i++){
				switch (i) {
				case 0:
					if(p.first-1>=0){
						if(!vis[p.first-1]){
							if(p.first-1==K){
								printf("%d\n",p.second+1);
								flag=true;
								break;
							}
							vis[p.first-1]=1;
							q.push(make_pair(p.first-1,p.second+1));
						}
					}
					
					break;
				case 1:
					if(p.first+1<=100000){
						if(!vis[p.first+1]){
							if(p.first+1==K){
								printf("%d\n",p.second+1);
								flag=true;
								break;
							}
							vis[p.first+1]=1;
							q.push(make_pair(p.first+1,p.second+1));
						}
					}
					
					break;
				case 2:
					if(p.first*2<=100000){
						if(!vis[p.first*2]){
							if(p.first*2==K){
								printf("%d\n",p.second+1);
								flag=true;
								break;
							}
							vis[p.first*2]=1;
							q.push(make_pair(p.first*2,p.second+1));
						}
					}
					
					break;
				}
			}
			if(flag) break;
		}
	}
	
	return 0;
}
