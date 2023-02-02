#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int max_n=10005;
const int K=26;
int N;
char ch[55];
char text[1000010];
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
Node *root,*superRoot;
void Init(){
	root=new Node;
	superRoot=new Node;
	root->fail=superRoot;
	for(int i=0;i<K;i++){
		superRoot->nxt[i]=root;
	}
	superRoot->count=-1;
}
void insertNode(char s[]){
	Node* t=root;
	int lens=strlen(s);
	for(int i=0;i<lens;i++){
		int c=s[i]-'a';
		if(t->nxt[c]==NULL){
			t->nxt[c]=new Node;
		}
		t=t->nxt[c];
	}
	t->count++;
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
				t->nxt[i]=t->fail->nxt[i]; //虚拟节点
			}
		}
	}
}
int query(char s[]){

	int ans=0;
	int lens=strlen(s);
	Node* t=root;
	for(int i=0;i<lens;i++){
		int c=s[i]-'a';
		t=t->nxt[c];
		for(Node* u=t;u->count!=-1;u=u->fail){
			ans+=u->count;
			u->count=-1;
		}
	}
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		Init();
		for(int i=0;i<N;i++){
			scanf("%s",ch);
			insertNode(ch);
		}
		build_ac();
		scanf("%s",text);
		printf("%d\n",query(text));
	}
	
	return 0;
}

