#include<cstdio>

const int max_n=1e5+10;
struct Node{
	int l,r;
	int val;
}node[max_n];

int N;
void add(int i,int j,bool flag){
	//flag为0，则j插到i的左边,1为j插到i的右边
	if(!flag){
		int pre=node[i].l;
		node[j].r=i;
		node[i].l=j;
		node[pre].r=j;
		node[j].l=pre;
	}else{
		int nxt=node[i].r;
		node[i].r=j;
		node[j].l=i;
		node[j].r=nxt;
		node[nxt].l=j;
	}
}
int main(){
	scanf("%d",&N);
	int head=0;
	node[head].l=node[head].r=0;
	node[1].val=1;
	add(0,1,1);
	int k,p;
	for(int i=2;i<=N;i++){
		scanf("%d %d",&k,&p);
		node[i].val=i;
		add(k,i,p);
	}
	int m;
	scanf("%d",&m);
	while(m--){
		scanf("%d",&k);
		if(node[k].l!=-1){
			int pre=node[k].l;
			int nxt=node[k].r;
			node[pre].r=nxt;
			node[nxt].l=pre;
			node[k].l=node[k].r=-1;
		}
	}
	int count=0;
	for(int i=node[head].r;i;i=node[i].r){
		if(count++) printf(" ");
		printf("%d",node[i].val);
	}
	printf("\n");
	return 0;
}
