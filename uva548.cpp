#include <iostream>
#include<sstream>
#include<string>
using namespace std;

const int max_n=10005;
int n,minSum,minV;
int post[max_n],inorder[max_n],lch[max_n],rch[max_n];
bool read(int *a){
	string s;
	getline(cin,s);
	stringstream ss(s);
	int x;
	n=0;
	while(ss>>x){
		a[n++]=x;
	}
	return n>0;
}
//l1是中序遍历，l2是后序遍历
int create_tree(int l1,int l2,int Len){
	if(Len<=0) return 0;
	int root=post[l2+Len-1];
	int index=0;
	while(inorder[l1+index]!=root) index++;
	lch[root]=create_tree(l1, l2, index); //左子树根节点的值
	rch[root]=create_tree(l1+index+1, l2+index, Len-index-1);//右子树根节点的值
	return root;
	
}
void getMin(int v,int sum){
	sum+=v;
	if(!lch[v]&&!rch[v]){
		if(sum<minSum||sum==minSum&&v<minV){
			minSum=sum;
			minV=v;
		}
	}
	if(lch[v]){
		getMin(lch[v],sum);
	}
	if(rch[v]){
		getMin(rch[v],sum);
	}
}
int main() {
	while(read(inorder)){
		read(post);
		create_tree(0, 0, n);
		minSum=0x3f3f3f3f;
		getMin(post[n-1],0);
		cout<<minV<<endl;
	}
	
	return 0;
}