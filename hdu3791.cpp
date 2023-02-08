#include<stdio.h>
#include<string>
#include<iostream>
#include<string.h>
using namespace std;

int N,cnt;
struct Tree{
	int ch;
	int left,right;
}tree1[101],tree2[101];

void build_tree(Tree tree[],int u,int k){
	if(tree[u].ch==-1){
		tree[u].ch=k;
		return;
	}
	if(tree[u].ch>k){
		if(tree[u].left==-1){
			tree[++cnt].ch=k;
			tree[u].left=cnt;
			
		}else{
			build_tree(tree,tree[u].left,k);
		}
	}else{
		if(tree[u].right==-1){
			tree[++cnt].ch=k;
			tree[u].right=cnt;
		}else{
			build_tree(tree,tree[u].right,k);
		}
	}
}
string preorder(Tree tree[],int u){
	string s="";
	if(u==-1){
		return s;
	}
	s+=char(tree[u].ch+'0');
	s+=preorder(tree,tree[u].left);
	s+=preorder(tree,tree[u].right);
	return s;
}
int main(){
	string s1,s2;
	while(scanf("%d",&N)&&N){
		memset(tree1,-1,sizeof(tree1));
		cin>>s1;
		cnt=1;
		for(int i=0;i<s1.size();i++){
			build_tree(tree1,1,s1[i]-'0');
		}
		string ss1=preorder(tree1,1);
		
		for(int i=0;i<N;i++){
			memset(tree2,-1,sizeof(tree2));
			cin>>s2;
			cnt=1;
			for(int j=0;j<s2.size();j++){
				build_tree(tree2,1,s2[j]-'0');
			}
			string ss2=preorder(tree2,1);
			
			if(ss1==ss2){
				cout<<"YES"<<endl;
			}else{
				cout<<"NO"<<endl;
			}
		}
		
	}
	return 0;
}
