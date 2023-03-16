#include<cstdio>
#include<cstring>
#include<algorithm>
#include<list>
#include<vector>
using namespace std;

const int block=2500;

list<vector<char> > List;
typedef list<vector<char> >::iterator it;
char ops[10];
it Find(int& pos){
	it i=List.begin();
	while(i!=List.end()&&pos>i->size()){
		pos-=i->size();
		i++;
	}
	return i;
}
it Next(it x){return ++x;}
void Split(it x,int pos){
	if(pos>=x->size()) return ;
	List.insert(Next(x),vector<char>(x->begin()+pos,x->end()));
	x->erase(x->begin()+pos,x->end());
}
void Merge(it x){
	x->insert(x->end(),Next(x)->begin(),Next(x)->end());
	List.erase(Next(x));
}
void Update(){
	for(it i=List.begin();i!=List.end();i++){
		while(i->size()>(block<<1)) Split(i,i->size()-block);
		while(Next(i)!=List.end()&&i->size()+Next(i)->size()<=block) Merge(i);
		while(Next(i)!=List.end()&&Next(i)->empty()) List.erase(Next(i));
	}
}
void Insert(int pos,const vector<char>& s){
	it x=Find(pos);
	if(!List.empty()) Split(x,pos);
	List.insert(Next(x),s);
	Update();
}
void Delete(int left,int right){
	it iter1=Find(left);Split(iter1,left);
	it iter2=Find(right);Split(iter2,right);
	iter2++;
	while(Next(iter1)!=iter2) List.erase(Next(iter1));
	Update();
}
void Output(int left,int right){
	it iter1=Find(left);
	it iter2=Find(right);
	for(it iter=iter1;;iter++){
		int a=iter==iter1?left:0;
		int b=iter==iter2?right:iter->size();
		for(int i=a;i<b;i++) putchar(iter->at(i));
		if(iter==iter2) break;
	}
	putchar('\n');
}
int main(){
	int t,n,pos;
	vector<char> s;
	scanf("%d",&t);
	while(t--){
		scanf("%s",ops);
		switch (ops[0]) {
		case 'M':
			scanf("%d",&pos);
			break;
		case 'I':
			scanf("%d",&n);
			s.clear();
			s.resize(n);
			for(int i=0;i<n;i++){
				s[i]=getchar();
				while(s[i]<32||s[i]>126) s[i]=getchar();
			}
			Insert(pos,s);
			break;
		case 'D':
			scanf("%d",&n);
			Delete(pos,pos+n);
			break;
		case 'G':
			scanf("%d",&n);
			Output(pos,pos+n);
			break;
		case 'P':
			pos--;
			break;
		case 'N':
			pos++;
			break;
		}
	}
	return 0;
}
