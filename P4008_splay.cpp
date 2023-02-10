#include<bits/stdc++.h>
using namespace std;
const int M = 2e6+10;
int cnt, root;
struct Node{int fa,ls,rs,size; char val;}t[M];   //tree[]存树;
void Update(int u){t[u].size = t[t[u].ls].size + t[t[u].rs].size+1;}  //用于排名
char str[M]={0};                //一次输入的字符串

int kth(int k,int u){
	if(t[t[u].ls].size+1==k) return u;
	if(t[t[u].ls].size>=k) return kth(k,t[u].ls);
	return kth(k-t[t[u].ls].size-1,t[u].rs);
}
void splay(int x,int goal){
	if(!goal) root=x;
	while(1){
		int f=t[x].fa,g=t[f].fa;
		if(f==goal) break;
	}
}
void Insert(int L,int len){
	int x=kth(L,root),y=kth(L+1,root);
	splay(x,0);
	splay(y,x);
}
int main(){
	t[1].size=2;    t[1].ls=2;  //小技巧：虚拟祖父，防止旋转时越界而出错
	t[2].size=1;    t[2].fa=1;  //小技巧：虚拟父亲
	t[1].fa=0;
	root=1; cnt=2;      //在操作过程中，root将指向字符串的根
	int pos=1;          //光标位置
	int n;   cin>>n;
	while(n--){
		int len;  char opt[10];  cin>>opt;
		if(opt[0]=='I'){
			cin>>len;
			for(int i=1;i<=len;i++){
				char ch=getchar();   while(ch<32||ch>126)  ch=getchar();
				str[i] = ch;
			}
			Insert(pos,len);
		}
		if(opt[0]=='D'){ cin>>len; del(pos,pos+len);}    //删除区间[pos+1,pos+len]
		if(opt[0]=='G'){
			cin>>len;     int x=kth(pos,root), y=kth(pos+len+1,root);
			splay(x,0);   splay(y,x);
			inorder(t[y].ls);    cout<<"\n";
		}
		if(opt[0]=='M'){ cin>>len; pos=len+1;}
		if(opt[0]=='P') pos--;
		if(opt[0]=='N') pos++;
	}
}

