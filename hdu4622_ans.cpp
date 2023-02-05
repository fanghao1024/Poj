#include <bits/stdc++.h>
using namespace std;
const int N = 2007;
int sz,last;          //sz: 结点（状态）的编号；last：指向最后被添加的结点
struct node{          //用字典树存结点
	int son[26];      //26个字母
	int father;
	int len;          //这个等价类的最大子串长度
}t[N<<1];                      //后缀自动机的状态数不超过2n个
void newNode(int length){      //建一个新结点。sz=0是根
	t[++sz].len = length;     //这个结点所表示的子串的长度
	t[sz].father = -1;        //它的父结点还未知
	memset(t[sz].son,0,sizeof(t[sz].son));
}
void init(){
	sz = -1; last = 0; //根是0，根指向-1，表示结束
	newNode(0);
}
void Insert(int c){
	newNode(t[last].len+1);
	int p = last, cur = sz;    //p:上个结点的位置，cur:新结点的位置
	while(p!=-1 && !t[p].son[c])
		t[p].son[c] = cur, p = t[p].father;
	if(p==-1)
		t[cur].father = 0;
	else{
		int q = t[p].son[c];
		if(t[q].len == t[p].len + 1)
			t[cur].father = q;
		else{        
			newNode(t[p].len+1);
			int nq = sz;             //复制结点
			memcpy(t[nq].son,t[q].son,sizeof(t[q].son));
			t[nq].father = t[q].father;
			t[cur].father = t[q].father = nq;
			while(p>=0 && t[p].son[c] == q)
				t[p].son[c] = nq,  p = t[p].father;
		}
	}
	last = cur;
	/* 打印后缀自动机的所有结点和边*/
	  for(int i=0;i<=sz;i++)
	  for(int j=0;j<26;j++)
	  if(t[i].son[j]) {  //起点-(边上的字符)-终点
	  int start=i,end=t[i].son[j];
	  printf("%d-(%c)-%d ",start,j+'a',end);
	  printf(" father=%d len=%d\n",t[end].father,t[end].len);
	  }
	  cout<<endl;
	 
}
char S[N];
int ans[N][N];
int main(){
	int T;    scanf("%d",&T);
	while(T--){
		scanf("%s",S);
		int n = strlen(S);
		for(int i = 0;i < n;i++){
			init();              //每次重新求S[i,j]的后缀自动机
			for(int j = i;j < n;j++){
				Insert(S[j]- 'a');
				ans[i][j] = ans[i][j-1] + t[last].len - t[t[last].father].len;
			}
		}
		int Q, L, R;    scanf("%d",&Q);
		while(Q--){
			scanf("%d%d",&L,&R);
			printf("%d\n",ans[--L][--R]);
		}
	}
	return 0;
}

