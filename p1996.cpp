#include<cstdio>
#include<cstring>

int N,M;
struct Node{
	int val;
	Node* nxt;
};
Node* head;
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		head=new Node;
		head->val=1;
		head->nxt=NULL;
		Node* now=head;
		Node* pre=head;
		for(int i=2;i<=N;i++){
			Node* p=new Node;
			p->val=i;
			p->nxt=NULL;
			now->nxt=p;
			pre=now;
			now=p;
		}
		now->nxt=head;
		int count=0;
		while(N--){
			for(int i=1;i<=M;i++){
				pre=now;
				now=now->nxt;
			}
			if(count++) printf(" ");
			printf("%d",now->val);
			pre->nxt=now->nxt;
			delete now;
			now=pre;
		}
		printf("\n");
	}
	return 0;
}
