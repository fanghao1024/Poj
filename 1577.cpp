#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
vector<string> vs;
int tree[3000];
struct BSTNode{
	char ch;
	BSTNode* left;
	BSTNode* right;
};
void insertTree(BSTNode* &T,char ch){
	if(!T){
		BSTNode* S=new BSTNode;
		S->ch=ch;
		S->left=NULL;
		S->right=NULL;
		T=S;
	}else{
		if(ch>T->ch){
			insertTree(T->right,ch);
		}else{
			insertTree(T->left,ch);
		}
	}
}
void showTree(BSTNode* &T){
	if(!T) return;
	cout<<T->ch;
	showTree(T->left);
	showTree(T->right);
}
int main(){
	string s;
	bool endflag=false;
	while(cin>>s){
		vs.clear();
		vs.push_back(s);
		while(cin>>s){
			if(s=="*"||s=="$"){
				if(s=="$") endflag=true;
				break;
			}
			vs.push_back(s);
		}
		reverse(vs.begin(),vs.end());
		memset(tree,-1,sizeof(tree));
		BSTNode* bst=NULL;
		for(int i=0;i<vs.size();i++){
			s=vs[i];
			for(int j=0;j<s.size();j++){
				insertTree(bst,s[j]);
			}
		}
		showTree(bst);
		cout<<endl;
		if(endflag) break;
	}
	return 0;
}
