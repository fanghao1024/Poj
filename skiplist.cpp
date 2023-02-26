#include<cstdio>
#include<cstdlib>
#include<ctime>

const int inf=0x3f3f3f3f;
const int MAX_LEVEL=16;
const int P=0.5f;

typedef struct Node{
	int val;
	struct Node* forward[MAX_LEVEL];
}*Nodeptr;
Nodeptr head,updata[MAX_LEVEL];
int level;

void init(){
	level=0;
	head=new Node;
	for(int i=0;i<MAX_LEVEL;i++) head->forward[i]=NULL;
	head->val=-inf;
}

Nodeptr Find(int val){
	Nodeptr p=head;
	for(int i=level;i>=0;i--){
		while(p->forward[i]&&p->forward[i]->val<val){
			p=p->forward[i];
		}
		updata[i]=p;
	}
	return p;
}

int RandLevel(){
	int lay=0;
	while((float)rand()/RAND_MAX<P&&lay<MAX_LEVEL-1) lay++;
	return lay;
}

void Insert(int val){
	Nodeptr p,s;
	int lay=RandLevel();
	if(lay>level) level=lay;
	p=Find(val);
	s=new Node;
	s->val=val;
	for(int i=0;i<MAX_LEVEL;i++){
		s->forward[i]=NULL;
	}
	for(int i=0;i<=lay;i++){
		s->forward[i]=updata[i]->forward[i];
		updata[i]->forward[i]=s;
	}
}

void Delete(int val){
	Nodeptr p=Find(val);
	if(p->forward[0]&&p->forward[0]->val==val){
		for(int i=level;i>=0;i--){
			if(updata[i]->forward[i]&&updata[i]->forward[i]->val==val)
				updata[i]->forward[i]=updata[i]->forward[i]->forward[i];
		}
		while(level&&!head->forward[level]) level--;
	}
}
