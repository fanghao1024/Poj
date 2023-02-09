#include <iostream>
#include<stdio.h>
using namespace std;

const int max_n=30010;
int rec[max_n];
int d[max_n];
int cnt[max_n];
int P;

void init(){
	for(int i=0;i<max_n;i++){
		rec[i]=i;
		d[i]=0;
		cnt[i]=1;
	}
}
int find(int x){
	int fx=rec[x];
	if(x!=rec[x]){
		rec[x]=find(rec[x]);
		d[x]+=d[fx];
	}
	return rec[x];
}
void unit(int x,int y){
	int a=find(x);
	int b=find(y);
	if(a!=b){
		rec[a]=b;
		d[a]=cnt[b];
		cnt[b]+=cnt[a];
	}
}

int main() {
	scanf("%d",&P);
	char ch;
	int x,y;
	init();
	while(P--){
		scanf(" %c",&ch);
		switch (ch) {
			case 'M':
				scanf("%d %d",&x,&y);
				unit(x,y);
				break;
			case 'C':
				scanf("%d",&x);
				find(x);
				printf("%d\n",d[x]);
				break;
		}
	}
	return 0;
}