#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int max_n=505;
const int max_p=205;
const int K=126-32;
int N,M,cnt,ids;
struct Node{
	Node* fail;
	Node* nxt[K];
	int count;
	Node(){
		fail=NULL;
		memset(nxt,NULL,sizeof(nxt));
		count=0;
	}
};
char words[max_p];
char text[10010];
bool res[510];
Node *root,*superRoot;
void Init(){
	root=new Node;
	superRoot=new Node;
	root->fail=superRoot;
	for(int i=0;i<K;i++){
		superRoot->nxt[i]=root;
	}
	superRoot->count=-1;
	ids=1;
}
void insertNode(char* s){
	int lens=strlen(s);
	Node* t=root;
	for(int i=0;i<lens;i++){
		int c=s[i]-33;
		if(t->nxt[c]==NULL){
			t->nxt[c]=new Node;
		}
		t=t->nxt[c];
	}
	t->count=ids++;
}
void build_ac(){
	queue<Node*> qn;
	qn.push(root);
	while(!qn.empty()){
		Node* t=qn.front();
		qn.pop();
		for(int i=0;i<K;i++){
			if(t->nxt[i]){
				t->nxt[i]->fail=t->fail->nxt[i];
				qn.push(t->nxt[i]);
			}else{
				t->nxt[i]=t->fail->nxt[i];
			}
		}
	}
}
bool query(char* s,int cn){
	bool flag=false;
	memset(res,0,sizeof(res));
	int lens=strlen(s);
	Node* t=root;
	int counts=0;
	for(int i=0;i<lens;i++){
		int c=s[i]-33;
		t=t->nxt[c];
		for(Node* u=t;u->count!=-1;u=u->fail){
			if(u->count>0){
				flag=true;
				counts++;
				res[u->count]=true;
			}
		}
	}
	
	if(counts>0){
		printf("web %d:",cn);
		for(int i=1;i<ids;i++){
			if(res[i])	printf(" %d",i);
		}
		printf("\n");
	}
	return flag;
}

int main(){
	scanf("%d",&N);
	Init();
	for(int i=1;i<=N;i++){
		scanf("%s",words);
		insertNode(words);
	}
	build_ac();
	scanf("%d",&M);
	int ans=0;
	for(int i=1;i<=M;i++){
		scanf("%s",text);
		ans+=query(text,i);
	}
	printf("total: %d\n",ans);
	
	return 0;	
}
