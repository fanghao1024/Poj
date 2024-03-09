#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
using namespace std;

int block=2500;

typedef list<vector<char> >::iterator it;
list<vector<char> > L;
int T,pos=0,n;
char ops[10],ch;
vector<char> s;
it find(int& pos){
	it i=L.begin();
	while(i!=L.end()&&pos>i->size()){
		pos-=i->size();
		i++;
	}
	return i;
}
it Next(it x){ return ++x;}
void split(it iter,int pos){
	if(pos==iter->size()) return ;
	L.insert(Next(iter),vector<char>(iter->begin()+pos,iter->end()));
	iter->erase(iter->begin()+pos,iter->end());
}
void merge(it x){
	x->insert(x->end(),Next(x)->begin(),Next(x)->end());
	L.erase(Next(x));
}
void update(){
	for(it i=L.begin();i!=L.end();i++){
		while(i->size()>=(block<<1)){
			split(i,i->size()-block);
		}
		while(Next(i)!=L.end()&&i->size()+Next(i)->size()<=block){
			merge(i);
		}
		while(Next(i)!=L.end()&&Next(i)->empty()){
			L.erase(Next(i));
		}
	}
}
void insert(int pos,const vector<char>& s){
	it iter=find(pos);
	if(!L.empty()) split(iter,pos);
	L.insert(Next(iter),s);
	update();
}
void Delete(int left,int right){
	it iter1=find(left);split(iter1,left);
	it iter2=find(right);split(iter2,right);
	iter2++;
	while(Next(iter1)!=iter2) L.erase(Next(iter1));
	update();
}
void output(int left,int right){
	it iter1=find(left);
	it iter2=find(right);
	for(it iter=iter1;;iter++){
		int a=iter==iter1?left:0;
		int b=iter==iter2?right:iter->size();
		for(int i=a;i<b;i++) putchar(iter->at(i));
		if(iter==iter2) break;
	}
	putchar('\n');
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",ops);
		switch (ops[0]) {
			case 'M':
				scanf("%d",&pos);
				break;
			case 'I':
				scanf("%d",&n);
				s.clear();s.resize(n);
				for(int i=0;i<n;i++){
					s[i]=getchar();
					while(s[i]<32||s[i]>126) s[i]=getchar();
				}
				insert(pos,s);
				break;
			case 'D':
				scanf("%d",&n);
				Delete(pos,pos+n);
				break;
			case 'G':
				scanf("%d",&n);
				output(pos,pos+n);
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
