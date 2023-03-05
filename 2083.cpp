#include<cstdio>
#include<cstring>
#include<cmath>
bool vis[2200][2200];
int cube[10];
void init(){
	cube[0]=1;
	for(int i=1;i<=7;i++) cube[i]=3*cube[i-1];
}
void build(int x1,int y1,int x2,int y2){
	if(x1==x2&&y1==y2) vis[x1][y1]=1;
	else{
		int dx=(x2-x1+1)/3,dy=(y2-y1+1)/3;
		build(x1,y1,x1+dx-1,y1+dy-1);
		build(x1+2*dx,y1,x2,y1+dy-1);
		build(x1+dx,y1+dy,x1+2*dx-1,y1+2*dy-1);
		build(x1,y2-dy+1,x1+dx-1,y2);
		build(x1+2*dx,y1+2*dy,x2,y2);
	}
}
int main(){
	int n;
	init();
	while(scanf("%d",&n)!=EOF){
		if(n==-1) break;
		memset(vis,0,sizeof(vis));
		n--;
		build(0,0,cube[n]-1,cube[n]-1);
		for(int i=0;i<=cube[n]-1;i++){
			for(int j=0;j<=cube[n]-1;j++){
				if(vis[i][j]) printf("X");
				else printf(" ");
			}
			printf("\n");
		}
		printf("-\n");
	}
	return 0;
}
