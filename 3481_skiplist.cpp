#include<cstdio>
#include<cstdlib>
#include<ctime>

const int MAX_LEVEL=16;
const int P=0.5f;
const int inf=0x3f3f3f3f;

struct Node{
	int K,P;
	Node* forward[MAX_LEVEL];
};
typedef Node* Nodeptr;
Nodeptr head,updata[MAX_LEVEL];
int level,min_k,max_k;
void init(){
	level=0;
	head=new Node;
	for(int i=0;i<MAX_LEVEL;i++) head->forward[i]=NULL;
	head->P=-inf;
	min_k=inf;
	max_k=-inf;
}

Nodeptr Find(int val){
	Nodeptr p=head;
	for(int i=level;i>=0;i--){
		while(p->forward[i]&&p->forward[i]->P<val)
			p=p->forward[i];
		updata[i]=p;
	}
	return p;
}
int RandLevel(){
	int lay=0;
	while((float)rand()/RAND_MAX<P&&lay<MAX_LEVEL-1) lay++;
	return lay;
}
int RandomLevel(){ //°´¹æÔòÑ¡ÔñÊý¾ÝÓ¦¸ÃÔÚÄÄ²ã²åÈë
	int lay=0;
	while(rand()%2&&lay<MAX_LEVEL-1)
		lay++;
	return lay;
}
void Inserts(int num,int val){
	Nodeptr p,s;
	if(val>max_k) max_k=val;
	if(val<min_k) min_k=val;
	int lay=RandomLevel();
	if(level<lay) level=lay;
	p=Find(val);
	s=new Node;
	s->K=num;
	s->P=val;
	for(int i=0;i<MAX_LEVEL;i++) s->forward[i]=NULL;
	for(int i=lay;i>=0;i--){
		s->forward[i]=updata[i]->forward[i];
		updata[i]->forward[i]=s;
	}
	
}


void Insert(int num,int val){
	if(val>max_k) max_k=val;
	if(val<min_k) min_k=val;
	Nodeptr p,s;
	int lay=RandLevel();
	if(lay>level) //Òª²åÈëµÄ²ã > ÏÖÓÐ²ãÊý
		level=lay;
	p=Find(val); //²éÑ¯ 
	s=new Node;//´´½¨Ò»¸öÐÂ½Úµã 
	s->K=num;
	s->P=val;
	for(int i=0;i<MAX_LEVEL;i++)
		s->forward[i]=NULL;
	for(int i=0;i<=lay;i++){//²åÈë²Ù×÷
		s->forward[i]=updata[i]->forward[i];
		updata[i]->forward[i]=s;
	}
}
void Delete(int val,bool flag){
	Nodeptr p=Find(val);
	if(p->forward[0]&&p->forward[0]->P==val){
		printf("%d\n",p->forward[0]->K);
		if(p->P==-inf&&!p->forward[0]->forward[0]) max_k=-inf,min_k=inf;
		else{
			if(flag){
				max_k=p->P;
			}else{
				min_k=p->forward[0]->forward[0]->P;
			}
		}
		for(int i=level;i>=0;i--){
			if(updata[i]->forward[i]&&updata[i]->forward[i]->P==val) 
				updata[i]->forward[i]=updata[i]->forward[i]->forward[i];
		}
		while(level&&!head->forward[level]) level--;
	}
}
void Operate(bool flag){
	int d;
	if(flag) d=max_k;
	else d=min_k;
	if(d==inf||d==-inf){
		printf("0\n");
		return ;
	}
	Delete(d,flag);
}

int main(){
	int ops,k,p;
	srand((unsigned int)time(0));
	init();
	while(scanf("%d",&ops)&&ops){
		switch(ops){
		case 1:
			scanf("%d %d",&k,&p);
			Insert(k,p);
			break;
		case 2:
			Operate(1);
			break;
		case 3:
			Operate(0);
			break;
		}
	}
	return 0;
}
