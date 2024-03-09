#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e7+10;

int rec[max_n];
int N,M;

int calPos(int x,int y){
	return (x-1)*M+y;
}
int main(){
	int x1,y1,x2,y2;
	int p,q;
	while(scanf("%d %d",&N,&M)!=EOF){
		scanf("%d",&p);
		while(p--){
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			rec[calPos(x1,y1)]++;
			rec[calPos(x1,y2+1)]--;
			rec[calPos(x1,y2+1)]--;
			rec[calPos(x2+1,y2+1)]++;
		}
	}
	return 0;
}
